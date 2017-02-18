/*
name-generator - name-generator.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <getopt.h>

#include <iostream>
#include <cstdlib>

#include "config.h"
#include "utils.h"
#include "names.h"

using namespace std;

static void print_version_flag() {
    fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: name-generator [options] RACE SUBRACE GENDER\n"
                "\t-h --help                   Print this help screen\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
          "See 'man name-generator' for more information [TODO add man pages].\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/* Option parser - parse_args(argc, argv)
    This function parses all cla's passed to argv. */
int parse_args(int argc, char* argv[], string* race, string* subrace, string* gender) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"version", no_argument,        0,  'v'},
        {"verbose", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hvV",
                               long_opts, &opt_ind)) != EOF) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h': {
            print_help_flag();
         } break;

        /* -v --version */
        case 'v': {
            print_version_flag();
        } break;

        /* -V --verbose */
        case 'V': {
            VB_FLAG = true;
            output("verbose flag is set\n", VB_CODE);
            QUIET_FLAG = false;
        } break;
        
        /* parsing error */
        case '?': {
            fprintf(stderr, "Error: unknown arguement %s\n", argv[optind]);
            print_help_flag();
        } break;
        
        /* if we get here something very bad happened */
        default: {
            status = output("Aborting...\n", EXIT_FAILURE);
        }
        }
    }

    /* check to make sure there are at least 
        two "unknown" args to parse throug*/
    switch(argc - optind) {
    case 1: {
        // TODO handle only one arg passed
        string opt0 = argv[optind++];

        /* we know they passed just a gender */
        if(opt0 == "male" || opt0 == "female") {
            *gender = opt0;
            break;
        } else {
            break;
        }
    } break;

    case 2: { 
        string opt0 = argv[optind++];
        string opt1 = argv[optind++];

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

    case 3: {
        string opt0 = argv[optind++];
        string opt1 = argv[optind++];
        string opt2 = argv[optind++];

        /* allows gender to be passed first */
        if(opt0 == "male" || opt0 == "female") {
            *gender = opt0;
            *race = opt1;
            *subrace = opt2;
            break;
        } else {
            *gender = opt1;
            *race = opt0;
            *subrace = opt2;
            break;
        }
    } break;

    default: {
        // TODO output error code
    }
    }

    return status;
}

int main(int argc, char* argv[]) {
    string race, subrace, gender;
    int status = output("parse_args completed\n", parse_args(argc, argv, &race, &subrace, &gender)); // may exit

    if(race.empty())   status = output("race cannot be empty\n", EXIT_FAILURE);
    if(gender.empty()) status = output("gender cannot be empty\n", EXIT_FAILURE);

    if(status == EXIT_SUCCESS) {
        output("found "+race+" "+gender+"\n", VB_CODE);

        NameGenerator gen(race, gender, subrace);

        output(gen.make_name() +'\n');
    }

    return output("exiting with status "+ to_string(status)+"\n", status);
}