/*
openrpg - openrpg.cpp
Created on: Nov 7, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include "config.h"
#include "utils.h"

using namespace std;

static void print_version_flag() {
    fputs("openrpg " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(0);
}

static void print_help_flag() {
    fputs("openrpg " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: openrpg [options]\n"
                "\t-h --help                   Print this help screen\n"
                "\t-n --name=RACE GENDER       Generate a random name of the given RACE and GENDER\n"
                "\t-q --quiet                  Do not print the banner on startup\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
          "General help using GNU software: <http://www.gnu.org/gethelp/>\n"
          "See 'man openrpg' for more information [TODO add man pages].\n",
          stdout);
    exit(0);
}

int main(int argc, char* argv[]) {
    int status = 0;

    if (argc > 1) {
        for(int i = 1; i < argc; i++) {
            string arg(argv[i]);

            if (arg == "-n" || arg == "--name") {
                string race, gender;
                
                if (argv[++i]) {
                    gender = argv[i];
                    if (argv[++i]) {
                        race = argv[i];
                        string cmd = "./generator " + gender + " " + race;
                        status = system(cmd.c_str());
                    } else {
                        status = 1;
                    }
                } else {
                    status = 1;
                }
                
            } else if (arg == "-r" || arg =="--roll") {
                if (argv[++i]) {
                    string cmd = "./roll " + (string)argv[i];
                    status = system(cmd.c_str());
                } else {
                    cout << "Missing sides!\n";
                    status = 1;
                }
                
            } else if (arg == "-v" || arg == "--verbose") {
                print_version_flag();
                status = 0;
            } else if(arg == "?" || arg == "-h" || arg == "--help") {
                print_help_flag();
            } else {
                cout << "Unknown argument!\n";
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