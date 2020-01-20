/*
openrpg - osx.h
Created on: Dec 30, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_OSX_H_
#define SRC_OSX_H_

/**
 * NOTE(incomingstick): This file is here to help define things that are osx specific. It may need
 * to be split in to multiple osx headers if it starts to cover more ground than just typedefs.
 **/

#ifdef __APPLE__
// Standard Library Headers
#include <string>

typedef unsigned int uint;
typedef unsigned long ulong;

std::string EXEC_PATH();
std::string CALL_PATH(void* func_ptr);

#endif /* __APPLE__ */
#endif /* SRC_OSX_H_ */
