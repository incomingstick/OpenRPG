/*
openrpg - utils.h
Created on: Mar 23, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <iostream>

#define CONTINUE_CODE  -2
#define OUTPUT_CODE    -1
#define VB_CODE         0
#define ERROR_CODE      1

extern bool VB_FLAG;
extern bool QUIET_FLAG;

size_t get_console_width();
size_t get_console_height();
std::string get_display_screen(std::string file);
std::string file_to_string(std::string fileName);
std::string leftpad(std::string str, int len = 0, char ch = ' ');
std::string rightpad(std::string str, int len = 0, char ch = ' ');
std::istream& safeGetline(std::istream& is, std::string& t);
bool print_file(std::string file);
int output(std::string log = "", int code = OUTPUT_CODE);

#endif /* SRC_UTILS_H_ */
