/*
openrpg - types.h
Created on: May 18, 2019

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_TYPES_H_
#define SRC_TYPES_H_

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include "exports/core_exports.h"
#else
#   define CORE_EXPORT
#endif

#include <cstdint>
#include <cstddef>
#include <climits>
#include <cfloat>

#include "platform.h"

typedef int8_t  CORE_EXPORT int8;
typedef int16_t CORE_EXPORT int16;
typedef int32_t CORE_EXPORT int32;
typedef int64_t CORE_EXPORT int64;
typedef int32   CORE_EXPORT bool32;

typedef uint8_t  CORE_EXPORT uint8;
typedef uint16_t CORE_EXPORT uint16;
typedef uint32_t CORE_EXPORT uint32;
typedef uint64_t CORE_EXPORT uint64;

typedef intptr_t  CORE_EXPORT intptr;
typedef uintptr_t CORE_EXPORT uintptr;

typedef size_t CORE_EXPORT memory_index;

typedef float  CORE_EXPORT real32;
typedef double CORE_EXPORT real64;

typedef int8   CORE_EXPORT i8;
typedef int8   CORE_EXPORT i08;
typedef int16  CORE_EXPORT i16;
typedef int32  CORE_EXPORT i32;
typedef int64  CORE_EXPORT i64;
typedef bool32 CORE_EXPORT b32;

typedef uint8  CORE_EXPORT u8;
typedef uint8  CORE_EXPORT u08;
typedef uint16 CORE_EXPORT u16;
typedef uint32 CORE_EXPORT u32;
typedef uint64 CORE_EXPORT u64;

typedef real32 CORE_EXPORT r32;
typedef real64 CORE_EXPORT r64;
typedef real32 CORE_EXPORT f32;
typedef real64 CORE_EXPORT f64;

#define flag8(type)  u8
#define flag16(type) u16
#define flag32(type) u32
#define flag64(type) u64

#define enum8(type)  u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

#define u16Max 65535
#define s32Min ((s32)0x80000000)
#define s32Max ((s32)0x7fffffff)
#define u32Min 0
#define u32Max ((u32)-1)
#define u64Max ((u64)-1)
#define f32Max FLT_MAX
#define f32Min -FLT_MAX

#define U32FromPointer(pointer) ((u32)(memory_index)(pointer))
#define pointerFromU32(type, value) (type *)((memory_index)value)

#define offsetOf(type, Member) (umm)&(((type *)0)->Member)

#define pi32  3.14159265358979323846f
#define tau32 6.28318530717958647692f

#define kilobytes(value) ((value)*1024LL)
#define megabytes(value) (kilobytes(value)*1024LL)
#define gigabytes(value) (megabytes(value)*1024LL)
#define terabytes(value) (gigabytes(value)*1024LL)

#endif /* SRC_TYPES_H_ */