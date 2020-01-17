/*
openrpg - unix.h
Created on: Dec 30, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_UNIX_H_
#define SRC_UNIX_H_

/**
 * NOTE(incomingstick): This file is here to help define things that are unix specific. It may need
 * to be split in to multiple unix headers if it starts to cover more ground than just typedefs.
 **/

#ifdef __unix__

typedef unsigned int uint;
typedef unsigned long ulong;

#endif /* __unix__ */
#endif /* SRC_UNIX_H_ */