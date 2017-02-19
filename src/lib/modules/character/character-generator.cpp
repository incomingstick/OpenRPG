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
                "\t-r --random                 Skips the character creator and generates a fully random character\n"
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
        {"random",  no_argument,        0,  'r'},
        {"version", no_argument,        0,  'v'},
        {"verbose", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "rhvV",
                               long_opts, &opt_ind)) != EOF &&
                               status != EXIT_FAILURE) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h': {
            print_help_flag();
        } break;

        /* -r --random */
        case 'r': {
            // TODO skip character creator and generate fully random character
        } break;

        /* -v --version */
        case 'v': {
            print_version_flag();
        } break;

        /* -V --verbose */
        case 'V': {
            VB_FLAG = true;
            QUIET_FLAG = false;
        } break;

        /* parsing error */
        case '?': {
            fprintf(stderr, "Error: unknown arguement %s\n", argv[optind]);
            print_help_flag();
        } break;

        /* if we get here something very bad happened */
        default: {
            printf("Aborting...\n");
            status = EXIT_FAILURE;
        }
        }
    }

    return status;
}

int main(int argc, char* argv[]) {
    int status = parse_args(argc, argv); // may exit

    /* begin creating the character here */
    printf("Use character creator (Y/n)\n");   // TODO character creator switch ('-r' argv will ALSO handle this)
    printf("Race\n");                          // TODO race menu
    printf("Subrace\n");                       // TODO subrace menu
    printf("Class\n");                         // TODO class menu
    printf("Background\n");                    // TODO background menu

    printf("\n");

    /* TODO Could this method of ability scoring work as a basis? */
    Ability abil;

    vector<int> stats = abil_arr();

    printf("You generated the following ability scores: \n");

    for(int num : stats) printf("%i (%i)\n", num, modifier(num));

    printf("\n");

    for(size_t i = 0; i < stats.size(); i++) {
        int score;

        switch(i) {
        case 0: {
            printf("Set Strength\t (STR): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.STR = score;
        } break;

        case 1: {
            printf("Set Dexterity\t (DEX): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.DEX = score;
        } break;

        case 2: {
            printf("Set Constitution (CON): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.CON = score;
        } break;

        case 3: {
            printf("Set Intelligence (INT): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.INT = score;
        } break;

        case 4: {
            printf("Set Wisdom\t (WIS): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.WIS = score;
        } break;

        case 5: {
            printf("Set Charisma\t (CHA): ");

            cin >> score;
            // TODO if score is not on the list??
            abil.CHA = score;
        } break;

        default: {
            printf("should not have gotten here");
            return EXIT_FAILURE;
        }
        }
    }

    printf("\n");

    printf("Skill select based on class\n");    // TODO Skill select based on class
    printf("Hit points\n");                     // TODO hit points max, avg, or roll + con mod
    printf("Equipment\n");                      // TODO select equipment based on class and background
    printf("Name:\n");                          // TODO read in name or generate random one?

    printf("\n");

    Character player(abil);

    printf("%s", player.to_string().c_str());

    return status;
}