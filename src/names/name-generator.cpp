/*
name-generator - name-generator.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>

#include "openrpg.h"
#include "names.h"

using namespace std;
using namespace ORPG;
using namespace ORPG::Names;

/**
  * @desc This function parses all cla's passed to argv from the command line.
  * This function may terminate the program.
  *
  * @param int argc - the number of arguments passed / the length of argv[]
  * @param char* argv[] - the arguments passed from the command line
  * @return int - an integer code following the C/C++ standard for program success
  */
int parse_args(int argc, char* argv[], string* race, string* gender) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    Core::opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct Core::option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"verbose", no_argument,        0,  'v'},
        {"version", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hvV",
                               long_opts, &opt_ind)) != EOF) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h': {
            Names::PRINT_HELP_FLAG();
         } break;

        /* -v --verbose*/
        case 'v': {
            Core::VB_FLAG = true;
            Core::QUIET_FLAG = false;
        } break;

        /* -V --version */
        case 'V': {
            Names::PRINT_VERSION_FLAG();
        } break;

        /* parsing error */
        case ':':
        case '?': {
            Names::PRINT_HELP_FLAG();
        } break;

        /* if we get here something very bad happened */
        default: {
            printf("Aborting...\n");
            status = EXIT_FAILURE;
        }
        }
    }

    /* check to make sure there are at least 
        two "unknown" args to parse throug*/
    switch(argc - Core::optind) {
    case 1: {
        string opt0 = argv[Core::optind++];
        *race = opt0;
    } break;
        
    case 2: { 
        string opt0 = argv[Core::optind++];
        string opt1 = argv[Core::optind++];

        // TODO: See TODO in default block below
        /* allows gender to be passed first */
        if(opt0 == "male" || opt0 == "female") {
            *gender = opt0;
            *race = opt1;
            break;
        } else {
            *gender = opt1;
            *race = opt0;
            break;
        }
    } break;

    default: {
        fprintf(stderr, "Error: Invalid number of arguments (expects 1 or 2 arguments)\n");
    }
    }

    return status;
}

/**
  * @desc entry point for the name-generator program. All command line
  * arguments are parsed before entering the name-generator program, and
  * the program may terminate before generating a name.
  *
  * @param string in - the users input to be parsed
  * @return int - an integer code following the C/C++ standard for program success
  */
int main(int argc, char* argv[]) {
    string race, gender;
    int status = parse_args(argc, argv, &race, &gender); // may exit

    if(race.empty()) {
        printf("Error: race cannot be empty\n");
        status = EXIT_FAILURE;
        Names::PRINT_HELP_FLAG();
    }

    if(status == EXIT_SUCCESS) {
        NameGenerator gen(race, gender);

        string name = gen.make_name();

        printf("%s\n", name.c_str());
    }

    return status;
}
