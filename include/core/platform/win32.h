/*
openrpg - win32.h
Created on: Aug 19, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_WIN32_H_
#define SRC_WIN32_H_

/**
 * NOTE(incomingstick): This file is here to help define things that are windows specific. It may need
 * to be split in to multiple win32 headers if it starts to cover more ground than just typedefs.
 **/

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "exports/core_exports.h"

typedef DWORD CORE_EXPORT uint;
typedef DWORDLONG CORE_EXPORT ulong;

const char* EXEC_PATH();

#endif /* _WIN32 */
#endif /* SRC_WIN32_H_ */