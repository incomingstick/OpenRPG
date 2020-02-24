/*
platform - win32.cpp
Created on: Jan 17, 2020

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
// OpenRPG Headers
#include "core/platform/win32.h"
#include "core/types.h"

// Standard Library Headers
#include <stdexcept>
#include <locale>

using namespace std;

void InitPlatform() {
    int err = 0;

    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        err = GetLastError();
        if(err != 0) fprintf(stderr, "Unable to open handel to terminal. Is this in a valid TTY shell? Error Number: %i", err);
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        err = GetLastError();
        if(err != 0) fprintf(stderr, "Unable to get console mode. Error Number: %i", err);
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        err = GetLastError();
        if(err != 0) fprintf(stderr, "Unable to set console mode. Error Number: %i", err);
    }

    return 0;
}

string EXEC_PATH() {
    char path[MAX_PATH] = { 0 };
    memory_index mem = GetModuleFileName(NULL, path, MAX_PATH);
    if(mem <= 0)
        throw runtime_error("EXEC_PATH Unable to read path to calling binary");
    
    return string(path);
}

string CALL_PATH(void* func_path) {
    char path[MAX_PATH];
    HMODULE hm = NULL;
    int err = 0;

    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR) func_path, &hm) == 0) {
        err = GetLastError();
        if(err != 0)
            throw runtime_error("CALL_PATH Unable to get module handle");
    }

    if (GetModuleFileName(hm, path, sizeof(path)) == 0) {
        err = GetLastError();
        if(err != 0)
            throw runtime_error("CALL_PATH Unable to get module path");
    }

    string retval(path);
    string winPrePath("\\\\?\\");
	size_t pos = retval.find(winPrePath);

    if(pos != std::string::npos) retval.erase(pos, winPrePath.length());

    return retval;
}
