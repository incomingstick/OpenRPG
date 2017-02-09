/*
openrpg - utils.h
Created on: Mar 23, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#include <unistd.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fstream>
#include <string>
#include <functional>
#include <random>

#include "config.h"
#include "utils.h"

using namespace std;

#ifdef TESTING_FLAG
#undef ASSET_LOC
#define ASSET_LOC TESTING_ASSET_LOC
#endif

string asset_loc = ASSET_LOC;

bool QUIET_FLAG = false;
bool VB_FLAG = false;

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
string get_display_screen(string file) {
    // Open the assets file for the current screen
    ifstream screen_file(asset_loc+"/"+file);
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
        output("file " + asset_loc + "/" + file + " could not be opened");
    }
    
    return ret;
}

/*
 * Converts the given file to an exact string copy
 * used to create images and other printed files.
 */
string file_to_string(string file) { 
	// Open the assets file for the current screen
    ifstream screen_file(asset_loc+"/"+file);
    string ret = "";
    
    if (screen_file.is_open()) {
        string buffer;
        
        while (getline(screen_file, buffer)) {
            ret = ret + buffer + '\n';
        }
        screen_file.close();
    }
    else {
        // TODO: Raise an exception here, if an asset file
        // cannot be opened then something serious has gone wrong.
        output("file " + asset_loc + "/" + file + " could not be opened");
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

// Taken from http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
std::istream& safeGetline(std::istream& is, std::string& t) {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

/*
 * Prints the text contents of the given file
 */
bool print_file(string type) {
    if(QUIET_FLAG) return false;
    string screen_disp = get_display_screen(type);
    output(screen_disp + '\n');
    return true;
}

/* Outputs the log string to stderr if VB_FLAG is set */
/* TODO improve output string for diff between verbose and debug output
    output should not print line tags (i.e [VERBOSE]) unless debug flag
    is set*/
int output(string log, int status_code) {
    switch(status_code) {
        case OUTPUT_CODE: {
            if(VB_FLAG)
                cout << "[OUTPUT]\t";
            
            // begin each new line with [OUTPUT] to align all debugging output
            for (auto it = log.begin(); it != log.end(); ++it) {
                // if the current index is needed:
                auto c = *it;

                cout << c;

                // access element as *it
                if(c == '\n' && VB_FLAG) {
                    if(it + 1 == log.end()) break;
                    else cout << "[OUTPUT]\t";
                }
            }
        } break;

        case VB_CODE: {
            if(VB_FLAG)
                cout << "[VERBOSE]\t" << log << endl;
        } break;

        case ERROR_CODE: {
            if(VB_FLAG)
                cerr << "[ERROR]\t" << log << endl;
        } break;

        default: {
            cout << log << endl;
        }
    }

    return status_code;
}

int random(int min, int max) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}