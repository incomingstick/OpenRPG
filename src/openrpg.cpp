/*
openrpg - openrpg.cpp
Created on: Nov 7, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include <getopt.h>
#include <vector>
#include <cstdlib>

#include "config.h"
#include "utils.h"

using namespace std;

static void print_version_flag() {
    fputs("openrpg " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
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
                "\t-r --roll=XdY               Simulates rolling dice\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
          "General help using GNU software: <http://www.gnu.org/gethelp/>\n"
          "See 'man openrpg' for more information [TODO add man pages].\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/* Option parser - parse_args(argc, argv)
    This function parses all cla's passed to argv. */
int parse_args(int argc, char* argv[]) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"name",    required_argument,  0,  'n'},
        {"quiet",   no_argument,        0,  'q'},
        {"roll",    required_argument,  0,  'r'},
        {"version", no_argument,        0,  'v'},
        {"verbose", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hn:qr:vV",
                               long_opts, &opt_ind)) != EOF) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h':
            print_help_flag();
            break;
        
        /* -n --name */
        case 'n':
            if(optind < argc) {
                cmd = "name-generator";
                if(VB_FLAG) cmd += " -V";
                cmd += " "+(string)optarg +" "+ (string)argv[optind++];
                
                verbose("calling "+cmd, EXIT_SUCCESS);
                verbose("called "+cmd, system(cmd.c_str()));
                verbose("exiting with status "+to_string(status), status);
                
                exit(status);
            } else {
                fprintf(stderr, "Error: invalid number of args 1 (expects 2)\n");
                print_help_flag();
            }
            break;
        
        /* -q --quiet */
        case 'q':
            QUIET_FLAG = true;
            verbose("turning verbose flag off");
            VB_FLAG = false;
            break;

        /* -r --roll */
        case 'r':
            if(optind <= argc) {
                cmd = "roll";
                if(VB_FLAG) cmd += " -V";
                cmd += " "+(string)optarg;
                
                verbose("calling "+cmd, EXIT_SUCCESS);
                verbose("called "+cmd, system(cmd.c_str()));
                verbose("exiting with status "+to_string(status), status);
                
                exit(status);
            } else {
                fprintf(stderr, "Error: invalid number of args\n");
                print_help_flag();
            }
            break;

        /* -v --version */
        case 'v':
            print_version_flag();
            break;

        /* -V --verbose */
        case 'V':
            VB_FLAG = true;
            verbose("verbose flag is set");
            QUIET_FLAG = false;
            break;
        
        /* parsing error */
        case '?':
            fprintf(stderr, "Error: unknown arguement %s\n", argv[optind]);
            print_help_flag();
            break;
        
        /* if we get here something very bad happened */
        default:
            status = verbose("Aborting...", EXIT_FAILURE);
        }
    }

    return status;
}

/* Parses text input into the console and determines the appropriate response/action */
int parse_input(string in) {
    int status = EXIT_SUCCESS;

    if (in.size() > 0) {
        // message to user that program is working to fulfill request
        verbose("parsing...");

        // parsed individual words
        vector<string> words;

        // temporary container for word being built
        string word;
    
        //standardizes inputs to ignore case
        for(int i = 0; (unsigned) i < in.size(); i++) {
            in[i] = tolower(in[i]);
            
            if((in[i] < '{' && in[i] > '`') || (in[i] < ':' && in[i] > '/') || in[i] == '+' || in[i] == '-') {
                word += in[i]; //pushes character to word
            } else if(word.size() > 0) {
                words.push_back(word); //end of word
                word = {}; //resets word
            }
        }
        
        if(word.size() > 0) words.push_back(word); //end of command word
        
        if (words.size() > 0) {
            verbose("Words (" + to_string(words.size()) + "): ");
            
            for(int i = 0; (unsigned) i < words.size();i++){
                cout << words[i];
                if((unsigned) i != words.size() - 1){
                    cout << ", ";
                }
            }
            
            cout << endl;
            
            //simple commands, must be expanded on based on command content
            if(words[0] == "exit" || words[0] == "quit" || words[0] == "q") {//quit program
                verbose("leaving input_parse("+ in +")");
                return EXIT_SUCCESS;
            } else if(words[0] == "gen" || words[0] == "generate") {
                if(words.size() > 2) {
                    string cmd = "./generator " + words[1] + " " + words[2];

                    verbose("calling "+cmd, EXIT_SUCCESS);
                    verbose("called "+cmd, system(cmd.c_str()));

                    return verbose("exiting with status "+to_string(status), status);
                } else {
                    cout << "Missing arguments!\n";
                }
            } else if(words[0] == "roll") {
                cout << "Preparing to roll some dice...\n";
                //roll(0);
                if(words.size() > 1) {
                    string cmd = "./roll ";
                    for (int i = 1; (unsigned) i < words.size(); i++) {
                        cmd += words[i] + " ";
                    }
                    
                    //string cmd = "./roll " + (string)words[1];
                    verbose("calling "+cmd, EXIT_SUCCESS);
                    verbose("called "+cmd, system(cmd.c_str()));

                    return verbose("exiting with status "+to_string(status), status);
                } else {
                    cout << "missing arguments\n";
                }
            } else { //default case
                cout << "Command not recognized!\n";
            }
            
            words = {};
        } else {
            cout << "No command!\n";
        }
    } else {
        verbose("No command!\n");
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    int status = verbose("parse_args completed", parse_args(argc, argv)); // may exit

    if(status == 0) {
        // TODO - clgui for program
        print_file("banners/welcome_mat1");
    
        string in("");

        // get user input
        while(status == 0) {
            cout << "\33[4morpg\33[0m > ";
            cin >> in;
            if(in == "exit" || in == "quit" || in == "q") {
                status = verbose(in+" command read", 0);
                break;
            }
            else status = verbose("called parse("+in+")", parse_input(in));
        }
    }

	return verbose("exiting with status "+to_string(status), status);
}