/*
openrpg - utils.h
Created on: Mar 23, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   ifndef utils_EXPORTS
#       define utils_EXPORTS
#   endif
#   include "exports/utils_exports.h"
#else
#   define UTILS_EXPORT
#endif

// these are orpg connonical exit and output codes
#define CONTINUE_CODE  -2
#define OUTPUT_CODE    -1
#define VB_CODE         0
#define ERROR_CODE      1

// Any useful keycodes go here
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77

bool UTILS_EXPORT VB_FLAG = false;
bool UTILS_EXPORT QUIET_FLAG = false;

size_t UTILS_EXPORT get_console_width();
size_t UTILS_EXPORT get_console_height();
std::string UTILS_EXPORT get_display_screen(std::string file);
std::string UTILS_EXPORT file_to_string(std::string fileName);
std::string UTILS_EXPORT leftpad(std::string str, int len = 0, char ch = ' ');
std::string UTILS_EXPORT rightpad(std::string str, int len = 0, char ch = ' ');
std::istream UTILS_EXPORT & safeGetline(std::istream& is, std::string& t);
bool UTILS_EXPORT print_file(std::string file);
int UTILS_EXPORT randomInt(int min, int max);
int UTILS_EXPORT gcd(int a, int b);

#endif /* SRC_UTILS_H_ */
