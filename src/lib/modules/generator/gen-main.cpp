/*
 * main.cpp
 *
 *  Created on: Nov 10, 2016
 */
#include <iostream>
#include "config.h"
#include "generator.h"

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
    for(int i = 0; i < argc; i++) {
        srand (time(NULL));//need a much better random number generator
        string race, gender;
        
        if(argv[++i]){
            gender = argv[i];
            if(argv[++i]){
                race = argv[i];
                nameGenerator(gender,race);
            }
        }else{
            return -1;
        }
    }
	return 0;
}