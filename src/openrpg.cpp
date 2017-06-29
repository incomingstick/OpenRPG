/*
openrpg - openrpg.cpp
Created on: Nov 7, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include <vector>
#include <string>

#include "openrpg.h"
#include "names.h"
#include "roll.h"

using namespace std;

static void print_version_flag() {
    fputs("openrpg " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("openrpg " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: openrpg [options]\n"
                "\t-h --help                   Print this help screen\n"
                "\t-n --name=RACE GENDER       Generate a random name of the given RACE and GENDER\n"
                "\t-q --quiet                  Do not print the banner on startup\n"
                "\t-r --roll=XdY               Simulates rolling dice\n"
                "\t-v --verbose                Verbose program output\n"
                "\t-V --version                Print version info\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
          "See 'man openrpg' for more information [TODO add man pages].\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/** 
 * Option parser - parse_args(argc, argv)
 * This function parses all cla's passed to argv.
 */
int parse_args(int argc, char* argv[]) {
    /* getopt_long stores the option and option index here */
    int opt = 0, opt_ind = 0;

    /* disables getopt printing to now be handled in '?' case */
    //opterr = 0;
    
    /* these are the long cla's and their corresponding chars */
    static struct option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"name",    required_argument,  0,  'n'},
        {"quiet",   no_argument,        0,  'q'},
        {"roll",    required_argument,  0,  'r'},
        {"version", no_argument,        0,  'V'},
        {"verbose", no_argument,        0,  'v'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hn:qr:vV",
                               long_opts, &opt_ind)) != EOF) {
        switch (opt) {
        /* -h --help */
        case 'h': {
            print_help_flag();
        } break;

        /* -n --name */
        case 'n': {
            NameGenerator name;

            if(optind < argc) {
                if((string)optarg == "male" || (string)optarg == "female") {
                    name.gender = (string)optarg;
                    name.race = (string)argv[optind++];
                } else {
                    name.race = (string)optarg;
                    name.gender = (string)argv[optind++];
                }
            } else if(optind == argc) {
                name.race = (string)optarg;
            } else {
                fprintf(stderr, "Error: invalid number of args (expects 1 or 2)\n");
                print_help_flag();
            }
            
            printf("%s\n", name.make_name().c_str());

            exit(EXIT_SUCCESS);
        } break;

        /* -q --quiet */
        case 'q': {
            QUIET_FLAG = true;
            VB_FLAG = false;
        } break;

        /* -r --roll */
        case 'r': {
            ExpressionTree tree;

            tree.set_expression(optarg);

            printf("%i\n", tree.parse_expression());

            exit(EXIT_SUCCESS);
        } break;

        /* -v --verbose */
        case 'v': {
            VB_FLAG = true;
            QUIET_FLAG = false;
        } break;

        /* -V --version */
        case 'V': {
            print_version_flag();
        } break;

        case ':':
        case '?': {
            print_help_flag();
        } break;

        /* if we get here something very bad happened */
        default: {
            fprintf(stderr, "Aborting...\n");
            exit(EXIT_FAILURE);
        }
        }
    }

    return CONTINUE_CODE;
}

/* TODO Parses text input into the console and determines the appropriate response/action */
int parse_input(string in) {
    if (in.size() > 0) {
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
            // TODO simple commands, must be expanded on based on command content
            if(words[0] == "exit" || words[0] == "quit" || words[0] == "q") {
                return EXIT_SUCCESS;
            } else if(words[0] == "gen" || words[0] == "generate") {

                if(words.size() >= 2) {
                    NameGenerator name;

                    if(words.size() >= 3) {
                        if(words[1] == "male" || words[1] == "female") {
                            name.gender = words[1];
                            name.race = words[2];
                        } else {
                            name.race = words[1];
                            name.gender = words[2];
                        }
                    } else if(words.size() == 2) {
                        name.race = words[1];
                    } else {
                        fprintf(stderr, "Error: invalid number of args (expects 1 or 2)\n");
                    }
                    
                    printf("%s\n", name.make_name().c_str());

                    return CONTINUE_CODE;;
                } else {
                    printf("Missing arguments!\n");
                }
            } else if(words[0] == "roll") {
                // TODO fix the roll command
                if(words.size() > 1) {
                    string exp;
                    for (int i = 1; (unsigned) i < words.size(); i++) {
                        exp += words[i];
                    }

                    ExpressionTree tree;

                    tree.set_expression(exp);

                    printf("%i\n", tree.parse_expression());

                    return CONTINUE_CODE;
                } else {
                    printf("Missing arguments\n");
                }
            } else { //default case
                printf("Command not recognized!\n");
            }
            words = {};
        } else {
            printf("No command given!\n");
        }
    } else {
        printf("No command given!\n");
    }
    
    return CONTINUE_CODE;
}

int main(int argc, char* argv[]) {
    int status = parse_args(argc, argv); // may exit
    
    if(status == CONTINUE_CODE) {
        // TODO - clgui for program
        print_file("banners/welcome_mat1");

        string in("");

        // get user input
        while(status == CONTINUE_CODE) {
            printf("\33[4morpg\33[0m > ");
            getline(cin, in);

            status = parse_input(in);
        }
    }

    return status;
}
