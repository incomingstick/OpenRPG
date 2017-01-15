/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
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
                string race, gender;
                
                if(argv[++i]){
                    gender = argv[i];
                    if(argv[++i]){
                        race = argv[i];
                        nameGenerator(gender,race);
                        status = 0;
                    }else{
                        status = 1;
                    }
                }else{
                    status = 1;
                }

            } else if(arg == "-r" || arg =="--roll"){
                if(argv[++i]){
                    int faces = atoi(argv[1]);
                    roll(faces);
                }else{
                    cout << "Missing sides!\n";
                    status = 1;
                }
                
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
        print_file("../assets/banners/welcome_mat1");
    
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
        }
    }
	return status;
}