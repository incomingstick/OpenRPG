/*
character-generator - character-generator.cpp
Created on: Jan 24, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <cctype>
#include <vector>
#include <string>

#include "openrpg.h"
#include "character.h"

using namespace std;
using namespace ORPG;
using namespace ORPG::Characters;

/**
 * @desc This function parses all cla's passed to argv from the command line.
 * This function may terminate the program.
 *
 * @param int argc - the number of arguments passed / the length of argv[]
 * @param char* argv[] - the arguments passed from the command line
 * @return int - an integer code following the C/C++ standard for program success
 **/
int parse_args(int argc, char* argv[]) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    Core::opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct Core::option long_opts[] = {
        {"help",    no_argument,        0,  'h'},
        {"random",  no_argument,        0,  'r'},
        {"version", no_argument,        0,  'v'},
        {"verbose", no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = Core::getopt_long(argc, argv, "rhvV",
                               long_opts, &opt_ind)) != EOF &&
                               status != EXIT_FAILURE) {

        switch (opt) {
        /* -h --help */
        case 'h': {
            print_help_flag();
        } break;

        /* -r --random */
        case 'r': {
            // TODO skip character creator and generate fully random character
        } break;

        /* -v --verbose */
        case 'v': {
            Core::VB_FLAG = true;
            Core::QUIET_FLAG = false;
        } break;

        /* -V --version */
        case 'V': {
            print_version_flag();
        } break;

        /* parsing error */
        case ':':
        case '?': {
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

/**
 * @desc entry point for the character-generator program. This contains the
 * main logic for creating a character via the character-generator. All
 * command line arguments are parsed before character creation begins, and
 * the program may terminate before allowing user input.
 *
 * @param string in - the users input to be parsed
 * @return int - an integer code following the C/C++ standard for program success
 **/
int main(int argc, char* argv[]) {
    int status = parse_args(argc, argv); // may exit

    /* begin creating the character here */
    printf("Use character creator (Y/n)\n");   // TODO character creator switch ('-r' argv should ALSO handle this)

    auto race = request_race();
    auto scores = request_scores();

    printf("Background\n");                    // TODO background menu

    printf("Class\n");                         // TODO class menu.
    printf("Skill select based on class\n");   // TODO Skill select based on class
    printf("Hit points\n");                    // TODO hit points max, avg, or roll + con mod

    printf("Equipment\n\n");                   // TODO select equipment based on class and background

    auto name = request_name();

    auto character = name.empty() ?
        new Character(scores, race) :
        new Character(scores, name, race);

    printf("%s", character->to_string().c_str());

    return status;
}
