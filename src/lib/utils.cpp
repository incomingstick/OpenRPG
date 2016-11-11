/*
 * utils.cpp
 *
 *  Created on: Mar 23, 2016
 *      Author: Tumblr
 */

#include <string>
#include <sys/ioctl.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include "utils.h"

using namespace std;

/*
 * Returns the width of the console
 */
size_t get_console_width() {
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	return size.ws_col;
}

/*
 * Returns the height of terminal
 */
size_t get_console_height() {
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	return size.ws_row;
}

/*
 * Loads the menu file of the given type to be used
 * for printing the UI
 */
string get_display_screen(string type) {
    // Open the assets file for the current screen
    ifstream screen_file("../src/assets/"+ type);
    string ret = "";
    
    if (screen_file.is_open()) {
        string buffer;
        
        while (getline(screen_file, buffer)) {
            // Append the formatted line to the cumulative string
            if(screen_file.peek() != EOF)
            	ret = ret + buffer + '\n';
            else ret = ret + buffer;
        }
        screen_file.close();
    }
    else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cout << "FILE COULD NOT BE OPENED" << endl;
    }
    
    return ret;
}

/*
 * Converts the given file to an exact string copy
 * used to create images and other printed files.
 */
string load_file(string file) { 
	// Open the assets file for the current screen
    ifstream screen_file("../src/assets/"+file);
    string  ret = "";
    
    if (screen_file.is_open()) {
        string  buffer;
        
        while (getline(screen_file, buffer)) {
            ret = ret + buffer + '\n';
        }
        screen_file.close();
    }
    else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        cout << "FILE COULD NOT BE OPENED" << endl;
    }
    
    return ret;
}

/* 
 * Example: str = "hi", len = "5", ch = '-'
 * Return: "---hi"
 */  
string leftpad(string str, int len, char ch) {
   int i = -1;
   
   len = len - str.size();
   if (len <= 0) return str; // doesn't need to pad

   while (++i < len) {
       str = ch + str;
   }
   
   return str;
}

/* 
 * Example: str = "hi", len = "5", ch = '-'
 * Return: "hi---"
 */ 
string rightpad(string str, int len, char ch) {
    int i = -1;
    
    len = len - str.size();
    if (len <= 0) return str; // doesn't need to pad
    
    while (++i < len) {
       str = str + ch;
   }
    
    return str;
}

/*
 * Prints the menu of the given string type to cout
 */
bool print_file(string type) {
    string screen_disp = get_display_screen(type);
    cout << screen_disp << endl;
    return true;
}