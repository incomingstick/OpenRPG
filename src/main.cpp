/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include "lib/config.h"
#include "lib/utils.h"

using namespace std;

/*
 * Input parser - parse(in)
 *      This function may become its own class if it grows
 *      large enough. For now it is simply a placeholder.
 */
int parse(string in) {
    cout << "parsing..." << endl;//message to user that program is working to fulfill request
    for(int i = 0; i < in.size();i++){//standardizes inputs to ignore case
        in[i] = toupper(in[i]);
    }
    
    if(in == "EXIT" || in == "QUIT" || in == "Q"){//quit program
        cout << "Quitting program...\n";
        return 0;
    }else if(in == "CMD1"){//placeholder command
        cout << "Running placeholder function 1!\n";
    }else if(in == "CMD2"){//placeholder command
        cout << "Running placeholder function 2!\n";
    }else{//default case
        cout << "Command not recognized!\n";
    }
    //string cmd("name-generator dwarf male"); // PLACEHOLDER VARIABLE
    //return system(cmd.c_str());;
}

bool print_file(string file){
    ifstream fileToPrint;
    fileToPrint.open(file);
    if(fileToPrint.is_open()){
        string line;
        while(getline(fileToPrint,line)){
            cout << line << "\n";
        }
        fileToPrint.close();
    }else{
        cout << "Error! Failed to load file.\n";
    }
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
        print_file("assets/banners/welcome_mat1");
    
        string in;
        
        cout << "Commands:\n1.) CMD1\n2.) CMD2\n3.) Quit\n\n";

        // get user input
        while(true) {
            cout << "\33[4morpg\33[0m > ";
            getline(cin, in);
            if(parse(in) == 0){
                break;
            }
            /*if(in == "exit" || in == "quit" || in == "q") break;
            else if((status = parse(in)) != 0) {
                return status;
            }*/
        }
    }

	return status;
}