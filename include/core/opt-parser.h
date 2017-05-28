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

#define BADCHAR  (int)'?'
#define BADARG   (int)':'
#define EMPTY    (char* )""

/* If we are on a unix system follow standard cla delimeter of '-'
   else we are on windows and we should follow the windows convention of
   using '/' to delim arguemnts

   TODO: Does windows allow use of long args? If so what is the syntax? */
#ifdef _WIN32

#define OP_DELIM '/'

#else /* assume unix */

#define OP_DELIM '-'

#endif

int  opterr   = 1;    // if error message should be printed
int  optind   = 1;    // index into parent argv array
int  optopt   = 0;    // character checked for validity
int  optreset = 0;    // reset getopt
char* optarg  = 0;    // argument associated with option

/* set optreset to 1 rather than these two */
static int nonopt_start = -1; // first non option argument (for permute)
static int nonopt_end = -1;   // first option after non options (for permute)


struct option
{
    const char *name;
    
    /* has_arg can't be an enum because some compilers complain about
       type mismatches in all the code that assumes it is an int. */
    int has_arg;
    int* flag;
    int val;
};

char* program_name(char* str) {
    char* ret;

    ret = strrchr(str, '/');
    if(ret)
        ret++;
    else
        ret = str;

    return ret;
}

/* Exchange the array block from start to end with the block
   from end to opt_end (keeping the same order of arguments
   in each array block). */
static void permute_args(int start,
                         int end,
                         int opt_end,
                         char* argv[])
{
    int cycle_start, cycle_len, cycle, nonopts, nopts, pos;
    char *swap;

    /* compute lengths of array blocks, number, size of cycles */
    nonopts = end - start;
    nopts = opt_end - end;
    cycle = gcd(nonopts, nopts);
    cycle_len = (opt_end - start) / cycle;

    for (int i = 0; i < cycle; i++) {
        cycle_start = end + i;
        pos = cycle_start;
        
        for (int j = 0; j < cycle_len; j++) {
            if (pos >= end) pos -= nonopts;
            else            pos += nopts;

            swap = argv[pos];
            /* linted const cast */
            ((char **)argv)[pos] = argv[cycle_start];

            /* linted const cast */
            ((char **)argv)[cycle_start] = swap;
        }
    }
}


/* This function is used to update pur scanning pointer */
int getopt_internal(int argc,
                    char* argv[],
                    const char *options) {
    /* option letter processing */
    static char* place = EMPTY;

    /* option letter list index */
    char* olli;

    /* reset our non-option start and end positions */
    if (optreset)
        nonopt_start = nonopt_end = -1;
    
    /* update scanning pointer */
    if (optreset || !*place) {
        optreset = 0;

        /* end of argument array */
        if (optind >= argc) {
            place = EMPTY;

            if (nonopt_end != -1) {
                /* do permutation, if we have to 
                   TODO: get this working!! */
                permute_args(nonopt_start, nonopt_end, optind, argv);

                optind -= nonopt_end - nonopt_start;
            } else if (nonopt_start != -1) {
                /* If we skipped non-options, set optind
                   to the first of them. */
                optind = nonopt_start;
            }
            
            nonopt_start = nonopt_end = -1;
            
            return EOF;
        }
        
        /* check if this is a non-option */
        if(*(place = argv[optind]) != OP_DELIM ||
           (place[1] == '\0' && strchr(options, '-') == NULL)) {
            place = EMPTY;
            
            /* if we found the first non-argument set the start there
               otherwise if we found the last non-argument then do a
               permutation 

               TODO: Get this working!!! */
            if (nonopt_start == -1)
                nonopt_start = optind;
            else if (nonopt_end != -1) {
                permute_args(nonopt_start, nonopt_end, optind, argv);

                nonopt_start = optind - (nonopt_end - nonopt_start);
                nonopt_end = -1;
            }
            
            optind++;
            
            return getopt_internal(argc, argv, options);
        }

        if (nonopt_start != -1 && nonopt_end == -1)
            nonopt_end = optind;

        /* If we have "-" do nothing, if "--" we are done */
        if (place[1] != '\0' && *++place == '-' && place[1] == '\0') {
            optind++;
            place = EMPTY;
            /* We found a long option (--), so if we skipped
               non-options, we have to permute. */
            if (nonopt_end != -1) {
                permute_args(nonopt_start, nonopt_end, optind, argv);
                optind -= nonopt_end - nonopt_start;
            }

            nonopt_start = nonopt_end = -1;

            return -1;
        }
        
        /* found "--" */
        if (place[1] && *++place == OP_DELIM) {
            /* ++optind; */
            place = EMPTY;

            return CONTINUE_CODE;
        }
    }
    
    /* option letter okay? */
    if ((optopt = (int)*place++) == BADARG ||
        !(olli = (char *)strchr(options, optopt))) {
        /*
         * if the user didn't specify OP_DELIM as an option,
         * assume it means EOF.
         */
        if (optopt == (int)OP_DELIM)
            return EOF;
        if (!*place)
            ++optind;
        if (opterr && *options != ':')
            (void)fprintf(stderr,
                          "%s: illegal option -- %c%s\n",
                          program_name(argv[0]), optopt, place);

        return BADCHAR;
    }
    if (*++olli != ':') {
        /* don't need argument */
        optarg = NULL;
        if (!*place)
            ++optind;
    } else {
        /* need an argument */
        
        /* no white space */
        if (*place)
            optarg = place;
        /* no arg */
        else if (argc <= ++optind) {
            place = EMPTY;
            if ((opterr) && (*options != ':'))
                (void)fprintf(stderr,
                              "%s: option requires an argument -- %c\n",
                              program_name(argv[0]), optopt);
            return BADARG;
        } else
            /* white space */
            optarg = argv[optind];
        
        place = EMPTY;
        ++optind;
    }

    /* dump back option letter */
    return optopt;
}

int getopt_long(int argc, char* argv[],
                const char* optstring,
                const struct option* longopts,
                int* index) {
    if(optstring == NULL)
        return EOF;

    /* lets make sure we don't
       check the program name */
    if(optind == 0)
        optind = optreset = 1;

    int retval = EOF;

    if ((retval = getopt_internal(argc, argv, optstring)) == CONTINUE_CODE) {
        char *current_argv = argv[optind++] + 2, *has_equal;
        int i, current_argv_len, match = EOF;

        /* Check to make sure we have not reached a null ('\0') terminator*/
        if (*current_argv == '\0') return EOF;

        /* if our option has a '=' after it (i.e openrpg --roll=5d6)
           then do not count it in our length */
        if ((has_equal = strchr(current_argv, '=')) != NULL) {
            current_argv_len = has_equal - current_argv;
            has_equal++;
        } else
            current_argv_len = strlen(current_argv);

        /* Check if our current option is in our list of longopts */
        for (i = 0; longopts[i].name; i++) {

            /* Move though the list until we find a match */
            if (strncmp(current_argv, longopts[i].name, current_argv_len))
                continue;

            if (strlen(longopts[i].name) == (unsigned)current_argv_len) {
                match = i;

                break;
            }

            /* something has gone wrong if we get here*/
            if (match == EOF) match = i;
        }

        /* if we found a match then lets check if it has an argument */
        if (match != EOF) {
            /* there could be an arguement! */
            if (longopts[match].has_arg == required_argument ||
                longopts[match].has_arg == optional_argument) {

                /* if there was an equal ('=') then lets move to it
                   otherwise just increment by 1 */
                if (has_equal)
                    optarg = has_equal;
                else
                    optarg = argv[optind++];
            }

            /* if an argument is required lets make sure we have it*/
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
                return (((*optstring == ':') ? BADARG : BADCHAR));
            }
        } else {
            /* No matching argument */
            if ((opterr) && (*optstring != ':'))
                fprintf(stderr,
                        "%s: illegal option -- %s\n",
                        program_name(argv[0]),
                        current_argv);
            return BADCHAR;
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
