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
#   include "core/win32.h"
#   include "exports/core_exports.h"
#else
#   define CORE_EXPORT
#endif

// these are orpg connonical exit and output codes
#define CONTINUE_CODE  -2
#define OUTPUT_CODE    -1
#define VB_CODE         0
#define ERROR_CODE      1

// Any useful keycodes go here
#define APOSTROPHE  39
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
        void CORE_EXPORT print_version_flag();

        /**
         * @desc prints the help info when -h or --help is an argument to the command.
         * This adhears to the GNU standard for help printing, and immediately terminates
         * the program with exit code EXIT_SUCCESS
         **/
        void CORE_EXPORT print_help_flag();

        /**
         * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void CORE_EXPORT print_basic_version();

        /**
         * @desc prints the help info when help, h, or H are called in the ORPG shell.
         * Because this is called from within our ORPG shell, the program will continue running.
         **/
        void CORE_EXPORT print_basic_help();

        /**
         * @desc returns a std::string of the preprocessor definition of VERSION
         * 
         * @return std::string - the preprocessor definition of VERSION
         **/
        std::string CORE_EXPORT version_string();

        extern bool CORE_EXPORT VB_FLAG;
        extern bool CORE_EXPORT QUIET_FLAG;

        /**
         * @desc searches the following directories to find our data location, returning false if it is unable
         * to locate the data, true otherwise:
         *      INSTALL_PREFIX,
         *      INSTALL_PREFIX/usr/share/
         *      INSTALL_PREFIX/usr/local/share/
         *      fs::current_path()
         *      fs::current_path().parent_path()
         * @return bool - returns false if unable to locate the data, true otherwise
         **/
        bool CORE_EXPORT LOCATE_DATA();

        /**
         * @desc returns the location of OpenRPG's data
         * 
         * @return string - the location of our data
         **/
        std::string CORE_EXPORT DATA_LOCATION();
    };
};

namespace ORPG {
    namespace Utils {
        /**
         * @desc Loads the menu file of the given type to be used
         * for printing the UI
         **/
        std::string CORE_EXPORT get_display_screen(std::string file);

        /**
         * @desc Converts the given file to an exact string copy
         * used to create images and other printed files.
         **/
        std::string CORE_EXPORT file_to_string(std::string fileName);

        // Taken from https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
        std::istream CORE_EXPORT & safeGetline(std::istream& is, std::string& t);

        /**
         * @desc Prints the text contents of the given file to stdout
         **/
        bool CORE_EXPORT print_file(std::string file);

        /**
         * @desc Example: str = "hi", len = "5", ch = '-'
         * Return: "---hi"
         **/
        std::string CORE_EXPORT leftpad(std::string str, int len = 0, char ch = ' ');

        /**
         * @desc Example: str = "hi", len = "5", ch = '-'
         * Return: "hi---"
         **/
        std::string CORE_EXPORT rightpad(std::string str, int len = 0, char ch = ' ');

        int CORE_EXPORT randomInt(int min, int max);

        bool CORE_EXPORT randomBool();

        /* Compute the greatest common divisor of a and b. */
        int CORE_EXPORT gcd(int a, int b);
    }
}

#endif /* SRC_UTILS_H_ */
