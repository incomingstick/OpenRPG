/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include <cstdio>
#include <limits.h>
#include <stdlib.h>
#include "config.h"
#include "utils.h"

using namespace std;

/*
 * Input parser - parse(in)
 *      This function may become its own class if it grows
 *      large enough. For now it is simply a placeholder.
 */
int parse(string in) {
    cout << "parsing..." << endl;
    string cmd("name-generator dwarf male"); // PLACEHOLDER VARIABLE
    return system(cmd.c_str());;
}

int main(int argc, char* argv[]) {
    int status = 0;

    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg(argv[i]);

            if(arg == "-n" || arg == "--name") {
                // TODO DANGEROUS - check integrity of array first
                string race(argv[++i]);
                string gender(argv[++i]);

                string cmd("name-generator "+race+" "+gender);
                
                // NOT HOW THIS SHOULD BE DONE
                status = system(cmd.c_str());
            } else if(arg == "-v" || arg == "--verbose") {
                fprintf(stdout,"%s v%d.%d.%d-%s\n",
                    argv[0],
                    OpenRPG_VERSION_MAJOR,
                    OpenRPG_VERSION_MINOR,
                    OpenRPG_VERSION_TWEAK,
                    OpenRPG_VERSION_SUFFIX);

                status = 0;
            }

            if(status != 0) exit(status);
        }
    } else {
        // TODO - cli-gui for program
        print_file("banners/welcome_mat1");
    
        string in("");

        // get user input
        while(true) {
            cout << "\33[4morpg\33[0m > ";
            cin >> in;
            if(in == "exit" || in == "quit" || in == "q") break;
            else if((status = parse(in)) != 0) {
                return status;
            }
        }
    }

	return status;
}