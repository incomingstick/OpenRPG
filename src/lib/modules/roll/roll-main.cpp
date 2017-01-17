/*
 * main.cpp
 *
 *  Created on: Jan 14, 2017
 *  Author: Devon Shustarich
 */
#include <iostream>
#include <string>
#include "config.h"
#include "roll.h"

using namespace std;

static void print_version_flag() {
    cout << "name-generator (openrpg) " << VERSION << " - " << COPYRIGHT << "\n"
          << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          << "This is free software: you are free to change and redistribute it.\n"
          << "There is NO WARRANTY, to the extent permitted by law.\n\n";
    exit(0);
}

static void print_help_flag() {
    fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: name-generator [options] RACE GENDER\n"
                "\t-h --help                   Print this help screen\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "General help using GNU software: <http://www.gnu.org/gethelp/>\n"
          "See 'man name-generator' for more information [TODO add man pages].\n",
          stdout);
    exit(0);
}

int main(int argc, char* argv[]) {
    srand (time(NULL));//need a much better random number generator
    int total = roll(argv[1]);
    for (int i = 2; i < argc; i += 2) {
        /*if (argv[++i]) {
            int faces = atoi(argv[i]);
            roll(faces);
        } else {
            cout << "missing sides\n";
        }*/
        if ((string) argv[i] == "+" && argv[i+1]) {
            total += roll(argv[i+1]);
        } else if ((string) argv[i] == "-" && argv[i+1]) {
            total -= roll(argv[i+1]);
        }
    }
    cout << total << endl;
	return total;
}