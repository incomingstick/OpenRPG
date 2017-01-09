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

    while (1) {
        static struct option long_options[] = {
            {"name",    required_argument, 0, 'n'},
            {"quiet",   no_argument,       0, 'q'},
            {"verbose", no_argument,       0, 'v'},
            {0,         0,                 0,  0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "n:qv",
                         long_options, &option_index);
        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
        case 'n':
            string cmd("name-generator dwarf male"); // PLACEHOLDER VARIABLE
            verbose("calling "+cmd, 0);
            verbose("called "+cmd, system(cmd.c_str()));
            status = 1;
            break;
        case 'q':
            QUIET_FLAG = true;
            verbose("turning verbose flag off");
            VB_FLAG = false;
            break;
        case 'v':
            VB_FLAG = true;
            verbose("verbose flag is set");
            QUIET_FLAG = false;
            break;
        case '?':
            /* getopt_long already printed an error message. */
            break;
        default:
            verbose("Aborting...", 0);
            abort();
        }
    }

    /* Print any remaining command line arguments (not options). */
    if (optind < argc) {
        printf ("non-option ARGV-elements: ");

        while (optind < argc) printf ("%s ", argv[optind++]);

        putchar ('\n');
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