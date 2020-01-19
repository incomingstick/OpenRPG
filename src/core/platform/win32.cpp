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

using namespace std;

string EXEC_PATH() {
    wchar_t path[MAX_PATH] = { 0 };
    memory_index mem = GetModuleFileNameW(NULL, path, MAX_PATH);
    if(mem <= 0)
        throw runtime_error("Unable to read path to calling binary");
    return string(path);
}

string CALL_PATH(void* func_path) {
    char path[MAX_PATH];
    HMODULE hm = NULL;

    if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR) &func_path, &hm) == 0)
    {
        int ret = GetLastError();
        fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
        // Return or however you want to handle an error.
    }
    if (GetModuleFileName(hm, path, sizeof(path)) == 0)
    {
        int ret = GetLastError();
        fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
        // Return or however you want to handle an error.
    }

    // The path variable should now contain the full filepath for this DLL.
}
