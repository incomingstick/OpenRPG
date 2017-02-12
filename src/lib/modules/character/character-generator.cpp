/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <getopt.h>

#include "config.h"
#include "utils.h"
#include "character.h"

using namespace std;

static void print_version_flag() {
    fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("character-generator (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: character-generator [options] RACE GENDER\n"
                "\t-h --help                   Print this help screen\n"
                "\t-v --version                Print version info\n"
                "\t-V --verbose                Verbose program output\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "General help using GNU software: <http://www.gnu.org/gethelp/>\n"
          "See 'man character-generator' for more information [TODO add man pages].\n",
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
            output("verbose flag is set", VB_CODE);
            QUIET_FLAG = false;
        } break;
        
        /* parsing error */
        case '?': {
            fprintf(stderr, "Error: unknown arguement %s\n", argv[optind]);
            print_help_flag();
        } break;
        
        /* if we get here something very bad happened */
        default: {
            status = output("Aborting...", EXIT_FAILURE);
        }
        }
    }

    return status;
}

int main(int argc, char* argv[]) {
    int status = output("parse_args completed", parse_args(argc, argv)); // may exit

    Character player;

    output("STR: "+ to_string(player.STR()) +"\n");
    output("DEX: "+ to_string(player.DEX()) +"\n");
    output("CON: "+ to_string(player.CON()) +"\n");
    output("INT: "+ to_string(player.INT()) +"\n");
    output("WIS: "+ to_string(player.WIS()) +"\n");
    output("CHA: "+ to_string(player.CHA()) +"\n");

    return output("exiting with status "+to_string(status), status);
}