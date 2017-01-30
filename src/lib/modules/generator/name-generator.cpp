/*
name-generator - name-generator.cpp
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>
#include <getopt.h>
#include <cstdlib>

#include "config.h"
#include "utils.h"
#include "generator.h"

using namespace std;

static void print_version_flag() {
    fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("name-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: name-generator [options] RACE GENDER\n"
                "\t-h --help                   Print this help screen\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
          "General help using GNU software: <http://www.gnu.org/gethelp/>\n"
          "See 'man name-generator' for more information [TODO add man pages].\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/* Option parser - parse_args(argc, argv)
    This function parses all cla's passed to argv. */
int parse_args(int argc, char* argv[], string* race, string* gender) {
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
        case 'h':
            print_help_flag();
            break;

        /* -v --version */
        case 'v':
            print_version_flag();
            break;

        /* -V --verbose */
        case 'V':
            VB_FLAG = true;
            output("verbose flag is set");
            QUIET_FLAG = false;
            break;
        
        /* parsing error */
        case '?':
            fprintf(stderr, "Error: unknown arguement %s\n", argv[optind]);
            print_help_flag();
            break;
        
        /* if we get here something very bad happened */
        default:
            status = output("Aborting...", EXIT_FAILURE);
        }
    }

    /* check to make sure there are at least 
        two "unknown" args to parse throug*/
    while (optind + 1 < argc) {
        string opt_str = argv[optind++];

        /* allows gender to be passed first */
        if(opt_str == "male" || opt_str == "female") {
            *gender = opt_str;
            *race = argv[optind];
            break;
        } else {
            *race = opt_str;
            *gender = argv[optind];
            break;
        }
    }

    return status;
}

int main(int argc, char* argv[]) {
    string race, gender;
    int status = output("parse_args completed", parse_args(argc, argv, &race, &gender)); // may exit

if(race.empty()) status =  output("race cannot be empty", EXIT_FAILURE);
    if(gender.empty()) status = output("gender cannot be empty", EXIT_FAILURE);

    if(status == EXIT_SUCCESS) {
        output("found "+race+" "+gender);

        NameGenerator gen(race, gender);

        cout << gen.make_name() << endl;
    }

	return output("exiting with status "+to_string(status), status);
}