/*
openrpg - platform.h
Created on: Dec 30, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_PLATFORM_H_
#define SRC_PLATFORM_H_

#ifdef _WIN32
#   include "platform/win32.h"
#endif

#ifdef __unix__
#   include "platform/unix.h"
#endif

#ifdef __APPLE__
#   include "platform/osx.h"
#endif

#endif /* SRC_PLATFORM_H_ */