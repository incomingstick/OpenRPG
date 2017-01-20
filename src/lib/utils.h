/*
openrpg - utils.h
Created on: Mar 23, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

extern bool QUIET_FLAG;
extern bool VB_FLAG;

size_t get_console_width();
size_t get_console_height();
std::string get_display_screen(std::string file);
std::string load_file(std::string fileName);
std::string leftpad(std::string str, int len = 0, char ch = ' ');
std::string rightpad(std::string str, int len = 0, char ch = ' ');
std::istream& safeGetline(std::istream& is, std::string& t);
bool print_file(std::string file);
int verbose(std::string log = "", int status = -1);
int parse_input(std::string in);

#endif /* SRC_UTILS_H_ */
