/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "config.h"
#include "utils.h"
#include "generator.h"
#include "roll.h"

using namespace std;

int main(int argc, char* argv[]) {
    int status = 0;

    srand (time(NULL));

    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg(argv[i]);

            if(arg == "-n" || arg == "--name") {
                // TODO DANGEROUS - check integrity of array first
                string race(argv[++i]);
                string gender(argv[++i]);
                
                nameGenerator(gender,race);

            } else if(arg == "-r" || arg =="--roll"){
                int faces = atoi(argv[++i]);
                roll(faces);
            }else if(arg == "-v" || arg == "--verbose") {
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
        print_file("assets/banners/welcome_mat1");
    
        string in;
        
        cout << "Current commands:\n1.) CMD1\n2.) ROLL\n3.) GENERATE NAME\n4.) Quit\n\n";
        cout << "\33[4morpg\33[0m > ";
        
        int code = 0;
        
        // get user input
        while(true) {
            if(code != 404){getline(cin, in);}//asks for input as long as the program is not shutting down
            
            if(code == 404){//exit
                break;
            }else if(code == 20){//rolled
                code = 0;//resets code
            }else{
                code = parse(in);
                if(code != 404){cout << "\33[4morpg\33[0m > ";}
            }
            /*if(in == "exit" || in == "quit" || in == "q") break;
            else if((status == parse(in)) != 0) {
                return status;
            }*/
        }
    }
	return status;
}