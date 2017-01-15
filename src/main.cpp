/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include "config.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]) {
    int status = 0;

    if(argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg(argv[i]);

            if(arg == "-n" || arg == "--name") {
                string race, gender;
                
                if(argv[++i]){
                    gender = argv[i];
                    if(argv[++i]){
                        race = argv[i];
                        //nameGenerator(gender,race);
                        string cmd = "./generator " + gender + " " + race;
                        status = system(cmd.c_str());
                    }else{
                        status = 1;
                    }
                }else{
                    status = 1;
                }

            } else if(arg == "-r" || arg =="--roll"){
                if(argv[++i]){
                    //int faces = argv[i];
                    //roll(faces);
                    string cmd = "./roll " + (string)argv[i];
                    status = system(cmd.c_str());
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
        cout << load_file("../assets/banners/welcome_mat1");
    
        string in;
        
        cout << "Current commands:\n1.) ROLL\n2.) GENERATE NAME\n3.) Quit\n\n";
        cout << "\33[4morpg\33[0m > ";
        
        int code = 0;
        
        // get user input
        while(true) {
            if(code != 404){getline(cin, in);}//asks for input as long as the program is not shutting down
            
            if(code == 404){//exit
                break;
            //}else if(code == 20){//rolled
                //code = 0;//resets code
            }else{
                code = parse(in);
                if(code != 404){cout << "\33[4morpg\33[0m > ";}
            }
        }
    }
	return status;
}