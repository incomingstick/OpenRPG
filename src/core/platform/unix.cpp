/*
platform - unix.cpp
Created on: Jan 17, 2020

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
// OpenRPG Headers
#include "core/platform/unix.h"
#include "core/types.h"

// POSIX / UNIX / LINUX Headers
#include <limits.h>
#include <unistd.h>
#include <dlfcn.h>

// Standard Library Headers
#include <string>
#include <stdexcept>

using namespace std;

// TODO Unix platform initialization stuff here
int InitPlatform() { return 0; }

string EXEC_PATH() {
    char path[PATH_MAX] = { 0 };
    memory_index mem = readlink("/proc/self/exe", path, PATH_MAX);
    if(mem <= 0)
        throw runtime_error("Unable to read path to calling binary");
    return string(path);
}

string CALL_PATH(void* func_ptr) {
    Dl_info dl_info;
    dladdr(func_ptr, &dl_info);
    return string(dl_info.dli_fname);
}
