/*
openrpg - utils.cpp
Created on: Mar 23, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
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
#   undef ASSET_LOC
#   define ASSET_LOC TESTING_ASSET_LOC
#endif

namespace ORPG::Core {
    /**
     * @desc prints the version info when -V or --version is an argument to the command.
     * This adhears to the GNU standard for version printing, and immediately terminates
     * the program with exit code EXIT_SUCCESS
     **/
    void print_version_flag() {
        fputs("openrpg " VERSION " - " COPYRIGHT "\n"
            "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n\n",
            stdout);
        exit(EXIT_SUCCESS);
    }

    /**
     * @desc prints the help info when -h or --help is an argument to the command.
     * This adhears to the GNU standard for help printing, and immediately terminates
     * the program with exit code EXIT_SUCCESS
     **/
    void print_help_flag() {
        fputs("openrpg " VERSION " - " COPYRIGHT "\n"
            "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n\n"
            "Usage: openrpg [options]\n"
                    "\t-h --help                   Print this help screen\n"
                    "\t-n --name=RACE GENDER       Generate a random name of the given RACE and GENDER\n"
                    "\t-q --quiet                  Do not print the banner on startup\n"
                    "\t-r --roll=XdY               Simulates rolling dice\n"
                    "\t-v --verbose                Verbose program output\n"
                    "\t-V --version                Print version info\n"
            "\n"
            "Long options may not be passed with a single dash.\n"
            "OpenRPG home page: <https://openrpg.io>\n"
            "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
            "See 'man openrpg' for more information [TODO add man pages].\n",
            stdout);
        exit(EXIT_SUCCESS);
    }

    /**
     * @desc prints the version info when version, ver, v, or V are called in the ORPG shell.
     * Because this is called from within our ORPG shell, the program will continue running.
     **/
    void print_basic_version() {
        fputs("openrpg " VERSION " - " COPYRIGHT "\n"
            "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n\n",
            stdout);
    }

    /**
     * @desc prints the help info when help, h, or H are called in the ORPG shell.
     * Because this is called from within our ORPG shell, the program will continue running.
     **/
    void print_basic_help() {
        fputs("openrpg " VERSION " - " COPYRIGHT "\n"
            "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n"
            "\n"
            "Usage: orpg > [command]\n"
            "\n"
            "Available commands:\n"
                    "\thelp (h) [module]                    Print the help screen for the given module. Omitting a\n"
                    "\t                                         module prints this help menu.\n"
                    "\tversion (ver, v | V)                 Print version info\n"
            "\n"
            "Available modules:\n"
                    "\tgenerate (gen, ng) [RACE | GENDER]   Generate a random name of the given RACE and GENDER\n"
                    "\troll (r) [XdY]                       Simulates rolling dice with Y sides X number of times\n"
            "\n"
            "Long options may not be passed with a single dash.\n"
            "OpenRPG home page: <https://openrpg.io>\n"
            "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
            "See 'man openrpg' for more information [TODO add man pages].\n",
            stdout);
    }
}

namespace ORPG::Utils {
    string asset_loc = ASSET_LOC;

    /**
     * Loads the menu file of the given type to be used
     * for printing the UI
     **/
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

    /**
     * Converts the given file to an exact string copy
     * used to create images and other printed files.
     **/
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

    // Taken from https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
    istream& safeGetline(istream& is, string& t) {
        t.clear();

        // The characters in the stream are read one-by-one using a std::streambuf.
        // That is faster than reading them one-by-one using the std::istream.
        // Code that uses streambuf this way must be guarded by a sentry object.
        // The sentry object performs various tasks,
        // such as thread synchronization and updating the stream state.

        istream::sentry se(is, true);
        auto sb = is.rdbuf();

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
                    is.setstate(ios::eofbit);
                return is;
            } break;
            default: {
                t += (char)c;
            }
            }
        }
    }

    /**
     * Prints the text contents of the given file to stdout
     **/
    bool print_file(string type) {
        if(Core::QUIET_FLAG) return false;

        string screen_disp = get_display_screen(type);
        printf("%s\n", screen_disp.c_str());

        return true;
    }

    /**
     * Example: str = "hi", len = "5", ch = '-'
     * Return: "---hi"
     **/
    string leftpad(string str, int len, char ch) {
    int i = -1;

    len = len - str.size();
    if (len <= 0) return str; // doesn't need to pad

    while (++i < len) {
        str = ch + str;
    }

    return str;
    }

    /**
     * Example: str = "hi", len = "5", ch = '-'
     * Return: "hi---"
     **/
    string rightpad(string str, int len, char ch) {
        int i = -1;

        len = len - str.size();
        if (len <= 0) return str; // doesn't need to pad

        while (++i < len) {
        str = str + ch;
    }

        return str;
    }

    int randomInt(int min, int max) {
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(min, max);

        return dist(mt);
    }

    /* Compute the greatest common divisor of a and b. */
    int gcd(int a, int b) {
        int c;

        c = a % b;
        while (c != 0) {
            a = b;
            b = c;
            c = a % b;
        }

        return b;
    }
}