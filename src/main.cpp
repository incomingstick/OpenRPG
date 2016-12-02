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

int main(int argc, char* argv[]) {
    for(int i = 1; i < argc; i++) {
        try {
            string arg(argv[i]);

            if(arg == "-n" || arg == "--name") {
                string race(argv[i + 1]);
                string gender(argv[i + 2]);

                string cmd("./modules/generator "+race+" "+gender);

                int status = system(cmd.c_str());

                exit(status);
            } else if(arg == "-v" || arg == "--verbose") {
                fprintf(stdout,"OpenRPG version %d.%d.%d-%s\n",
                        OpenRPG_VERSION_MAJOR,
                        OpenRPG_VERSION_MINOR,
                        OpenRPG_VERSION_TWEAK,
                        OpenRPG_VERSION_SUFFIX);

                int status = 0;

                exit(status);
            }
        } catch(...) {
            cerr << "invalid arg/use print" << endl;
        }

        exit(0);
    }

    print_file("banners/welcome_mat1");
    
    string in("");

    while(in != "exit") {
        cout << "\33[4morpg\33[0m > ";
        cin >> in;
    }

	return 0;
}