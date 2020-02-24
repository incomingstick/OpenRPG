/*
openrpg - openrpg.cpp
Created on: Nov 7, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
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
using namespace ORPG;

/**
 * TODO hold in memory a history of the commands run in the current session
 * and allow use of the UP and DOWN arrow keys to move through this list
 *
 * NOTE: We should make this finite, based on a changeable setting, up to a max of 1000 lines
 **/
vector<string> commandHistory;

/**
 * @desc This function parses all cla's passed to argv from the command line.
 * This function may terminate the program.
 *
 * @param int argc - the number of arguments passed / the length of argv[]
 * @param char* argv[] - the arguments passed from the command line
 * @return int - an integer code following the C/C++ standard for program success
 **/
int parse_args(int argc, char* argv[]) {
    /* getopt_long stores the option and option index here */
    int opt = 0, opt_ind = 0;

    /* these are the long cla's and their corresponding chars */
    static struct Core::option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"name",    required_argument,  0,  'n'},
        {"quiet",   no_argument,        0,  'q'},
        {"roll",    required_argument,  0,  'r'},
        {"verbose", no_argument,        0,  'v'},
        {"version", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hn:qr:vV", long_opts, &opt_ind))
			!= EOF) {
        switch (opt) {
			/* -h --help */
			case 'h': {
				Core::print_help_flag();
			} break;

			/* -n --name */
			case 'n': {
				NameGenerator name;

				if(Core::optind < argc) {
					if((string)Core::optarg == "male" || (string)Core::optarg == "female") {
                        name.set_gender((string)Core::optarg);
						name.set_race((string)argv[Core::optind++]);
					} else {
						name.set_race((string)Core::optarg);
						name.set_gender((string)argv[Core::optind++]);
					}
				} else if(Core::optind == argc) {
					name.set_race((string)Core::optarg);
				} else {
					fprintf(stderr, "Error: invalid number of args (expects 1 or 2)\n");
					Core::print_help_flag();
				}
				printf("%s\n", name.make_name().c_str());
				exit(EXIT_SUCCESS);
			} break;

			/* -q --quiet */
			case 'q': {
				Core::QUIET_FLAG = true;
				Core::VB_FLAG = false;
			} break;

			/* -r --roll */
			case 'r': {
				ExpressionTree tree;
				tree.set_expression(Core::optarg);
				printf("%i\n", tree.parse_expression());
				exit(EXIT_SUCCESS);
			} break;

			/* -v --verbose */
			case 'v': {
				Core::VB_FLAG = true;
				Core::QUIET_FLAG = false;
			} break;

			/* -V --version */
			case 'V': {
				Core::print_version_flag();
			} break;

			case ':':
			case '?': {
				Core::print_help_flag();
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

/**
 * @desc parse input is our ORPG shell. This takes in the users input string and parses
 * it out based on our logic. This function may terminate the program.
 *
 * @param string in - the users input to be parsed
 * @return int - an integer code following the C/C++ standard for program success
 **/
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

		//end of command word
        if(word.size() > 0)
			words.push_back(word);

        if (words.size() > 0) {
            // TODO simple commands, must be expanded on based on command content
            // NOTE add character-generator when it's finished
            if(words[0] == "exit" || words[0] == "quit" || words[0] == "q") {
                return EXIT_SUCCESS;
            } else if(words[0] == "generate" || words[0] == "gen" || words[0] == "ng") {
                if(words.size() >= 2) {
                    NameGenerator name;
                    if(words.size() >= 3) {
                        // TODO add nonbinary genders (a la warforged) and/or shortcuts
                        if(words[1] == "male" || words[1] == "female") {
                            name.set_gender(words[1]);
                            name.set_race(words[2]);
                        } else {
                            name.set_race(words[1]);
                            name.set_gender(words[2]);
                        }
                    } else if(words.size() == 2) {
                        name.set_race(words[1]);
                    } else {
                        fprintf(stderr, "Error: invalid number of args (expects 1 or 2)\n");
                    }
                    printf("%s\n", name.make_name().c_str());
                    return CONTINUE_CODE;
                } else {
                    printf("Missing arguments!\n");

                    Names::print_basic_help();

                    return CONTINUE_CODE;
                }
            } else if(words[0] == "roll" || words[0] == "r") {
                // TODO fix the roll command
                if(words.size() > 1) {
                    string exp;
                    for (int i = 1; (unsigned) i < words.size(); i++) {
                        exp += words[i];
                    }
                    ExpressionTree tree;
                    if(tree.set_expression(exp))
                        printf("%i\n", tree.parse_expression());
                    return CONTINUE_CODE;
                } else {
                    printf("Missing arguments\n");

                    Roll::print_basic_help();

                    return CONTINUE_CODE;
                }
            } else if(words[0] == "help" || words[0] == "h" || words[0] == "H") {
                /*
				 * TODO complete the help command as follows
                 *    The help command should print in a similar format
                 *    to the '-h' arguement, but should be expanded on in
                 *    the TUI. Each command will have its own help section
                 *    i.e calling `help roll` will display the roll modules
                 *    TUI formatted help command. This should hold true for
                 *    all modules callable from within the TUI.
                 */
                if(words.size() > 1) {
                    if(words[1] == "roll" || words[1] == "r") {
                        Roll::print_basic_help();

                        return CONTINUE_CODE;
                    } else if(words[1] == "generate" || words[1] == "gen" || words[1] == "ng") {
                        Names::print_basic_help();

                        return CONTINUE_CODE;
                    } else {
                        Core::print_basic_help();

                        return CONTINUE_CODE;
                    }
                } else {
                    Core::print_basic_help();

                    return CONTINUE_CODE;
                }
            } else if (words[0] == "version" || words[0] == "ver" || words[0] == "v" || words[0] == "V") {
                /* Prints print_version_string() without exiting */
                Core::print_basic_version();

                return CONTINUE_CODE;
            } else {
                printf("Command not recognized!\n");

                return CONTINUE_CODE;
            } /* default case for words array */
            words = {};
        } else {
            printf("No command given!\n");

            return CONTINUE_CODE;
        } /* END if (words.size() > 0) */
    } else {
        printf("No command given!\n");

        return CONTINUE_CODE;
    } /* END if (in.size() > 0) */

    // should never get here!
    return EXIT_FAILURE;
}

/**
 * @desc entry point for the ORPG program. This contains the main loop for the ORPG
 * shell. All command line arguments are parsed before entering the ORPG shell, and
 * the program may terminate before allowing user input.
 *
 * @param string in - the users input to be parsed
 * @return int - an integer code following the C/C++ standard for program success
 **/
int main(int argc, char* argv[]) {
    // Initialize any platform specfic features such as Windows terminal sequences
    InitPlatform();

    int status = parse_args(argc, argv); // may exit

    if(status == CONTINUE_CODE) {
        if(!Core::QUIET_FLAG) {
            // TODO - add more banners and randomly pick one
            Utils::print_file("banners/welcome_mat1");
        }

        string in("");

        // get user input
        while(status == CONTINUE_CODE) {
            printf("\33[4morpg\33[0m > ");

            Utils::safeGetline(cin, in);
            status = parse_input(in);
        }
    }
    
    return status;
}
