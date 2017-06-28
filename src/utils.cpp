/*
openrpg - utils.h
Created on: Mar 23, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 */
#include <fstream>
#include <string>
#include <functional>
#include <random>

#include "core/config.h"
#include "core/utils.h"

using namespace std;

#ifdef TESTING_FLAG
#undef ASSET_LOC
#define ASSET_LOC TESTING_ASSET_LOC
#endif

string asset_loc = ASSET_LOC;

bool QUIET_FLAG = false;
bool VB_FLAG = false;

/*
 * Loads the menu file of the given type to be used
 * for printing the UI
 */
string get_display_screen(string file) {
    // Open the data file for the current screen
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
        printf("file %s/%s could not be opened\n", asset_loc.c_str(), file.c_str());
    }
    
    return ret;
}

/*
 * Converts the given file to an exact string copy
 * used to create images and other printed files.
 */
string file_to_string(string file) { 
    // Open the data file for the current screen
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
        printf("file %s/%s could not be opened\n", asset_loc.c_str(), file.c_str());
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
        case '\n': {
            return is;
        } break;

        case '\r': {
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        } break;

        case EOF: {
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        } break;
        default: {
            t += (char)c;
        }
        }
    }
}

/*
 * Prints the text contents of the given file
 */
bool print_file(string type) {
    if(QUIET_FLAG) return false;

    string screen_disp = get_display_screen(type);
    printf("%s\n", screen_disp.c_str());
    
    return true;
}

int random(int min, int max) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

/* Compute the greatest common divisor of a and b. */
int gcd(int a, int b)
{
    int c;

    c = a % b;
    while (c != 0) {
        a = b;
        b = c;
        c = a % b;
    }

    return b;
}

