/*
roll - roll.cpp
Created on: Nov 10, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <string>

#include "openrpg.h"
#include "roll/roll-parser.h"

using namespace std;

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
                "\t-v --verbose                Verbose program output\n"
                "\t-V --version                Print version info\n"
          "\n"
          "Long options may not be passed with a single dash.\n"
          "Report bugs to: <https://github.com/incomingstick/OpenRPG/issues>\n"
          "OpenRPG home page: <https://github.com/incomingstick/OpenRPG>\n"
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
        {"verbose",     no_argument,        0,  'v'},
        {"version",     no_argument,        0,  'V'},
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

        /* -V --verbose */
        case 'v': {
            VB_FLAG = true;
            QUIET_FLAG = false;
        } break;

        /* -v --version */
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

    int status = parse_args(argc, argv, &inputString);
    
    if(status == EXIT_SUCCESS) {
        ExpressionTree tree;

        if(tree.set_expression(inputString)) {
            if(VB_FLAG) printf("%s", tree.to_string().c_str());
            
            printf("%i\n", tree.parse_expression());
        } else {
            // TODO: improve error output
            fprintf(stderr, "Invalid expression - %s\n", inputString.c_str());
        }
    }

    return status;
}
