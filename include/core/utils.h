/*
openrpg - utils.h
Created on: Mar 23, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
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

namespace ORPG {
    namespace Core {
        /**
         * @desc prints the version info when -V or --version is an argument to the command.
         * This adhears to the GNU standard for version printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void UTILS_EXPORT print_version_flag();

        /**
         * @desc prints the help info when -h or --help is an argument to the command.
         * This adhears to the GNU standard for help printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void UTILS_EXPORT print_help_flag();

        /**
         * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void UTILS_EXPORT print_basic_version();

        /**
         * @desc prints the help info when help, h, or H are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void UTILS_EXPORT print_basic_help();

        bool UTILS_EXPORT VB_FLAG = false;
        bool UTILS_EXPORT QUIET_FLAG = false;
    };
};

namespace ORPG {
    namespace Utils {
        /**
         * Loads the menu file of the given type to be used
         * for printing the UI
         **/
        std::string UTILS_EXPORT get_display_screen(std::string file);

        /**
         * Converts the given file to an exact string copy
         * used to create images and other printed files.
         **/
        std::string UTILS_EXPORT file_to_string(std::string fileName);

        // Taken from https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
        std::istream UTILS_EXPORT & safeGetline(std::istream& is, std::string& t);

        /**
         * Prints the text contents of the given file to stdout
         **/
        bool UTILS_EXPORT print_file(std::string file);

        /**
         * Example: str = "hi", len = "5", ch = '-'
         * Return: "---hi"
         **/
        std::string UTILS_EXPORT leftpad(std::string str, int len = 0, char ch = ' ');

        /**
         * Example: str = "hi", len = "5", ch = '-'
         * Return: "hi---"
         **/
        std::string UTILS_EXPORT rightpad(std::string str, int len = 0, char ch = ' ');

        int UTILS_EXPORT randomInt(int min, int max);

        /* Compute the greatest common divisor of a and b. */
        int UTILS_EXPORT gcd(int a, int b);
    }
}

#endif /* SRC_UTILS_H_ */
