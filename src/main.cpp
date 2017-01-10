/*
 * main.cpp
 *
 *  Created on: Nov 7, 2016
 */
#include <iostream>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <getopt.h>
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
                "\t-V                          Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "See 'man openrpg' for more information [TODO add man pages].\n",
          stdout);
    exit(0);
}

/*
 * Input parser - parse_input(in)
 *      This function may become its own class if it grows
 *      large enough. For now it is simply a placeholder.
 */
int parse_input(string in) {
    verbose("parsing... "+in, 0);
    string cmd("name-generator dwarf male"); // PLACEHOLDER VARIABLE
    verbose("calling "+cmd, 0);
    return verbose("called "+cmd, system(cmd.c_str()));
}

/*
 * Option parser - parse_option(in)
 *      This function parses all cla's passed to argv. When a bad arg
 *      is passed prints usage menu.
 */
int parse_opt(int argc, char* argv[]) {
    int status = 0;
    int c;

    /* getopt_long stores the option index here. */
    int option_index = 0;

    /* disables getopt printing to now be handled in '?' case */
    opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct option long_options[] = {
        {"help",    no_argument,        0,  'h'},
        {"name",    required_argument,  0,  'n'},
        {"quiet",   no_argument,        0,  'q'},
        {"verbose", no_argument,        0,  'V'},
        {"version", no_argument,        0,  'v'},
        /* NULL row to terminate struct */
        {0,         0,                 0,  0}
    };

    while ((c = getopt_long (argc, argv, "hn:qv",
                             long_options, &option_index)) != -1) {
        string cmd("");

        switch (c) {
        /* -h --help */
        case 'h':
            print_help_flag();
            break;
        
        /* -n --name */
        case 'n':
            if(optind < argc) {
                cmd = "name-generator "+ (string)optarg +" "+ (string)argv[optind++];
                verbose("calling "+cmd, 0);
                verbose("called "+cmd, system(cmd.c_str()));
            }
            exit(0);
            break;
        
        /* -q --quiet */
        case 'q':
            QUIET_FLAG = true;
            verbose("turning verbose flag off");
            VB_FLAG = false;
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
            /* getopt_long already printed an error message. */
            break;
        
        /* if we get here something very bad happened */
        default:
            verbose("Aborting...", 0);
            abort();
        }
    }

    return status;
}

int main(int argc, char* argv[]) {
    int status = verbose("parse_opt completed", parse_opt(argc, argv));

    if(status == 0) {
        // TODO - cli-gui for program
        print_file("banners/welcome_mat1");
    
        string in("");

        // get user input
        while(status == 0) {
            cout << "\33[4morpg\33[0m > ";
            cin >> in;
            if(in == "exit" || in == "quit" || in == "q") {
                status = verbose("exiting program", 0);
                break;
            }
            else status = verbose("called parse("+in+")", parse_input(in));
        }
    }

	return status;
}