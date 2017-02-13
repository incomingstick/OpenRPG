/*
roll - roll.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <getopt.h>

#include <string>

#include "config.h"
#include "utils.h"
#include "roll-parser.h"

using namespace std;

bool POS_FLAG;
bool SUM_FLAG;

/**
  * @desc prints the current compiled version
  * @return void - always exits with status EXIT_SUCCESS
  */
static void print_version_flag() {
    fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

/**
  * @desc prints the help and usage menu
  * @return void - always exits with status EXIT_SUCCESS
  */
static void print_help_flag() {
    fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
          "OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n"
          "Usage: roll [options] XdY [+|-] AdB [+|-] N [...]\n"
                "\t-h --help                   Print this help screen\n"
                "\t-p --positive               Allow only positive results\n"
                "\t-s --sum-series             Show the sum of roll series\n"
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

/**
  * @desc parses through the arguements passed by char* argv[] and runs
  *     program logic realted to those arguements. This function may
  *     exit the program
  * @param int argc - length of argv as an integer
  * @param char* argv[] - an array of cstrings read from the command line
  * @return int - signifies the stats of the function call, 0 for success
  */
int parse_args(int argc, char* argv[], string* inputString) {
    int status = EXIT_SUCCESS;

    /* getopt_long stores the option and option index here */
    int opt, opt_ind;

    /* disables getopt printing to now be handled in '?' case */
    opterr = 0;

    /* these are the long cla's and their corresponding chars */
    static struct option long_opts[] = {
        {"help",        no_argument,        0,  'h'},
        {"positive",    no_argument,        0,  'p'},
        {"sum-series",  no_argument,        0,  's'},
        {"version",     no_argument,        0,  'v'},
        {"verbose",     no_argument,        0,  'V'},
        /* NULL row to terminate struct */
        {0,         0,                  0,   0}
    };

    while ((opt = getopt_long(argc, argv, "hpsvV",
                               long_opts, &opt_ind)) != EOF) {
        string cmd("");

        switch (opt) {
        /* -h --help */
        case 'h': {
            print_help_flag();
        } break;

        /* -p --positive */
        case 'p': {
            POS_FLAG = true;
        } break;
        
        /* -s --sum-series */
        case 's': {
            SUM_FLAG = true;
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

    string expression;

    argc -= optind;
    argv += optind;         
  
    /* build expression string to parse */
    while(argc > 0) {
        expression += *argv;

        argc--;
        argv++;
    }

    if (expression.size() > 0) *inputString = expression;
    else *inputString = "1d20";

    return status;
}

/**
  * @desc parses through the arguements passed by char* argv[] and runs
  *     program logic realted to those arguements. This function may
  *     exit the program
  * @param int argc - length of argv as an integer
  * @param char* argv[] - an array of cstrings read from the command line
  * @return int - signifies the stats of the function call, 0 for success
  */
int main(int argc, char* argv[]) {
    string inputString;
    int status = output("parse_args completed", parse_args(argc, argv, &inputString));

    ExpressionTree tree;

    tree.set_expression(inputString);
    tree.parse_expression();

    return output("exiting with status "+to_string(status), status);
}