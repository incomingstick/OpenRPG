/*
openrpg - opt-parser.h
Created on: Mar 29, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef OPT_PARSER_H
#define OPT_PARSER_H

#include <cstring>

#define no_argument          0
#define required_argument    1
#define optional_argument    2

int  opterr;    /* if error message should be printed */
int  optind;    /* index into parent argv vector */
int  optopt;    /* character checked for validity */
int  optreset;  /* reset getopt */
char* optarg;   /* argument associated with option */

struct option
{
    const char *name;
    
    /* has_arg can't be an enum because some compilers complain about
       type mismatches in all the code that assumes it is an int.  */
    int has_arg;
    int *flag;
    int val;
};

char* program_name(char* str) {
    char* retval;

    retval = strrchr(str, '/');
    if(retval)
        retval++;
    else
        retval = str;

    return retval;
}

int getopt_internal(int argc,
                    char* const argv[],
                    const char *ostr) {
    /* option letter processing */
    static char* place = (char* )"";

    /* option letter list index */
    char* oli;
    
    /* update scanning pointer */
    if (optreset || !*place) {
        optreset = 0;
        if (optind >= argc || *(place = argv[optind]) != '-') {
            place = (char* )"";
            return -1;
        }
        
        /* found "--" */
        if (place[1] && *++place == '-') {
            /* ++optind; */
            place = (char* )"";
            return -2;
        }
    }

    /* option letter okay? */
    if ((optopt = (int)*place++) == (int)':' ||
        !(oli = (char *)strchr(ostr, optopt))) {
        /*
         * if the user didn't specify '-' as an option,
         * assume it means -1.
         */
        if (optopt == (int)'-')
            return -1;
        if (!*place)
            ++optind;
        if (opterr && *ostr != ':')
            (void)fprintf(stderr,
                          "%s: illegal option -- %c\n",
                          program_name(argv[0]), optopt);

        return *((int* )"?");
    }
    if (*++oli != ':') {
        /* don't need argument */
        optarg = NULL;
        if (!*place)
            ++optind;
    } else {/* need an argument */
        if (*place)/* no white space */
            optarg = place;
        else if (argc <= ++optind) {/* no arg */
            place = (char* )"";
            if ((opterr) && (*ostr != ':'))
                (void)fprintf(stderr,
                              "%s: option requires an argument -- %c\n",
                              program_name(argv[0]), optopt);
            return (int)':';
        } else/* white space */
            optarg = argv[optind];
        place = (char* )"";
        ++optind;
    }
    return (optopt);/* dump back option letter */
}

int getopt_long(int argc, char* const argv[],
                const char* optstring,
                const struct option* longopts,
                int* index) {
    int retval = -1;

    if ((retval = getopt_internal(argc, argv, optstring)) == -2) {
        char *current_argv = argv[optind++] + 2, *has_equal;
        int i, current_argv_len, match = -1;

        if (*current_argv == '\0') {
            return -1;
        }
        if ((has_equal = strchr(current_argv, '=')) != NULL) {
            current_argv_len = has_equal - current_argv;
            has_equal++;
        } else
            current_argv_len = strlen(current_argv);

        for (i = 0; longopts[i].name; i++) {
            if (strncmp(current_argv, longopts[i].name, current_argv_len))
                continue;

            if (strlen(longopts[i].name) == (unsigned)current_argv_len) {
                match = i;
                break;
            }
            if (match == -1)
                match = i;
        }
        if (match != -1) {
            if (longopts[match].has_arg == required_argument ||
                longopts[match].has_arg == optional_argument) {
                if (has_equal)
                    optarg = has_equal;
                else
                    optarg = argv[optind++];
            }
            if ((longopts[match].has_arg == required_argument)
                && (optarg == NULL)) {
                /*
                 * Missing argument, leading :
                 * indicates no error should be generated
                 */
                if ((opterr) && (*optstring != ':'))
                    fprintf(stderr,
                            "%s: option requires an argument -- %s\n",
                            program_name(argv[0]),
                            current_argv);
                return (((*optstring == ':') ? (int)':' : (int)'?'));
            }
        } else { /* No matching argument */
            if ((opterr) && (*optstring != ':'))
                fprintf(stderr,
                        "%s: illegal option -- %s\n",
                        program_name(argv[0]),
                        current_argv);
            return (int)'?';
        }
        if (longopts[match].flag) {
            *longopts[match].flag = longopts[match].val;
            retval = 0;
        } else
            retval = longopts[match].val;
        if (index)
            *index = match;
    }
    
    return retval;
}

#endif /* OPT_PARSER_H */
