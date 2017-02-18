/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <getopt.h>
#include <vector>

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

    return status;
}

int main(int argc, char* argv[]) {
    int status = output("parse_args completed\n", parse_args(argc, argv)); // may exit

    /* begin creating the character here */
    output("Use character creator (Y/n)\n");   // TODO character creator switch
    output("Race\n");                          // TODO race menu
    output("Subrace\n");                       // TODO subrace menu
    output("Class\n");                         // TODO class menu
    output("Background\n");                    // TODO background menu

    output("\n");

    /* TODO Could this method of ability scoring work as a basis? */
    Ability abil;

    vector<int> stats = abil_arr();

    output("You generated the following ability scores: \n");

    for(int num : stats) output(to_string(num) + " ("+to_string(modifier(num))+")\n");

    output("\n");

    for(size_t i = 0; i < stats.size(); i++) {
        int score;

        switch(i) {
        case 0: {
            output("Set Strength\t (STR): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.STR = score;
        } break;

        case 1: {
            output("Set Dexterity\t (DEX): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.DEX = score;
        } break;

        case 2: {
            output("Set Constitution (CON): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.CON = score;
        } break;

        case 3: {
            output("Set Intelligence (INT): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.INT = score;
        } break;

        case 4: {
            output("Set Wisdom\t (WIS): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.WIS = score;
        } break;

        case 5: {
            output("Set Charisma\t (CHA): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.CHA = score;
        } break;

        default: {
            return output("should not have gotten here", EXIT_FAILURE);
        }
        }
    }

    output("\n");

    output("Skill select based on class\n");    // TODO Skill select based on class
    output("Hit points\n");                     // TODO hit points max, avg, or roll + con mod
    output("Equipment\n");                      // TODO select equipment based on class and background
    output("Name:\n");

    output("\n");

    Character player(abil);

    output(player.to_string());

    return output("exiting with status "+to_string(status)+"\n", status);
}