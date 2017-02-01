/*
roll - roll.cpp
Created on: Nov 10, 2016

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include "roll.h"

using namespace std;

extern bool POS_FLAG;
extern bool SUM_FLAG;

#ifndef yyconst
#define yyconst const
#endif

static void print_version_flag() {
    fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law.\n\n",
          stdout);
    exit(EXIT_SUCCESS);
}

static void print_help_flag() {
    fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
          "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n"
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
        case 'h':
            print_help_flag();
            break;

        /* -p --positive */
        case 'p':
            POS_FLAG = true;
            break;
        
        /* -s --sum-series */
        case 's':
            SUM_FLAG = true;
            break;

        /* -v --version */
        case 'v':
            print_version_flag();
            break;

        /* -V --verbose */
        case 'V':
            VB_FLAG = true;
            output("verbose flag is set", VB_CODE);
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

    string expression;

    argc -= optind;
    argv += optind;         
  
    /* build expression string to parse */
    while(argc > 0) {
        expression += *argv;

        argc--;
        argv++;
    }

    if (expression.size() > 0) {
        globalInputString = expression.c_str();

        yyparse();
    } else {
        yyparse();
    }

    return status;
}

int main(int argc, char* argv[]) {
    int status = output("parse_args completed", parse_args(argc, argv));

	return output("exiting with status "+to_string(status), status);
}

int read_string(char *buff, int *numBytesRead, int maxBytesToRead) {
    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = strlen(globalInputString) - globalReadOffset;
    
    if(numBytesToRead > bytesRemaining) { numBytesToRead = bytesRemaining; }
    
    for(int i = 0; i < numBytesToRead; i++)
        buff[i] = globalInputString[globalReadOffset+i];
    
    *numBytesRead = numBytesToRead;
    globalReadOffset += numBytesToRead;
    
    return 0;
}

struct parse_node* allocate_node(void) {
    struct parse_node* node = (parse_node*) malloc(sizeof(struct parse_node));
    
    if(node == NULL) {
        output("out of memory", VB_CODE);
        exit(output("exiting with status "+to_string(EXIT_FAILURE), EXIT_FAILURE));
    }

    /* initialize default values */
    node->left  = NULL;
    node->right = NULL;
    node->next  = NULL;
    node->op    = 0;
    node->value = 0;
  
    return node;
}

struct parse_node* new_number(int number) {
    struct parse_node* node = allocate_node();
    
    node->op = OP_NUMBER;
    node->value = number;

    return node;
}

int compare(const void* p1, const void* p2) {
    const int i1 = *((const int *)p1);
    const int i2 = *((const int *)p2);

    if (i1 > i2) return 1;
    else if (i1 < i2) return -1;
    else return 0;
}

struct parse_node* new_op (unsigned short int op, struct parse_node* left, struct parse_node* right) {
    struct parse_node* node = allocate_node();
    
    node->op = op;
    node->value = 0;
    node->left = left;
    node->right = right;
    
    return node;
  
}

struct parse_node* new_dice (struct parse_node* sides) {
    struct parse_node* node = allocate_node();
  
    node->op = OP_DICE;
    node->value = 0;
    node->right = sides;
    
    return node;
}

int checked_sum(int op1, int op2) {
    if ((op2 > 0 && op1 > INT_MAX - op2) || (op2 < 0 && op1 < INT_MIN - op2))
    output("overflow", ERROR_CODE);
    
    return op1+op2;
}

int checked_multiplication(int op1, int op2) {
    int result = op1 * op2;
    if(op1 != 0 && result / op1 != op2 ) {
        output("overflow", ERROR_CODE);
    }
    
    return result;
}

void print_node(struct parse_node* node) {
    switch(node->op) {
    case OP_NUMBER: printf("number (%i)", node->value); break;      
    case OP_DICE:   printf("dice"); break;
    case OP_PLUS:   printf("+"); break;
    case OP_MINUS:  printf("-"); break;
    case OP_TIMES:  printf("*"); break;
    case OP_DIV:    printf("/"); break;
    case OP_HIGH:   printf("high"); break;
    case OP_LOW:    printf("low"); break;
    case OP_GT:     printf(">"); break;
    case OP_GE:     printf(">="); break;
    case OP_LT:     printf("<"); break;
    case OP_LE:     printf("<="); break;
    case OP_NE:     printf("!="); break;
    case OP_REP:    printf("rep"); break;
    default :       printf("unknown node"); break;
    }
}

void print_tree(std::string prefix, struct parse_node* node, int indent) {
    int i;
  
    printf("[%s]\t\t", prefix.c_str());

    for(i = 0; i < indent; i++) {
        printf(" ");
    }

    print_node(node);

    printf("\n");

    if(node->left != NULL) {
        print_tree(prefix, node->left, indent+1);
    }

    if(node->right != NULL) {
        print_tree(prefix, node->right, indent+1);
    }
}

int roll_expression(struct parse_node* node, bool print) {
    int high;
    int i;
    int limit;
    int low;
    int repetitions;
    int return_value = 0;
    int sides;
    int tmp;
    int* results;

    struct parse_node* cur;

    cur = node;
    while (cur != NULL) {
        int sum = 0;

        switch(cur->op) {
        case OP_NUMBER:
            sum = cur->value;
            break;

        case OP_REP:
            for (i = 0; i < roll_expression(cur->left, false); i++)
                sum = checked_sum(sum, roll_expression(cur->right, false));
            break;
      
        case OP_DICE: {
                Die die(roll_expression(cur->right, false));
                sum = die.roll();
            }
            break;
      
        case OP_PLUS:
            sum = checked_sum(roll_expression(cur->left, false),
                              roll_expression(cur->right, false));
            break;
      
        case OP_MINUS:
            sum = checked_sum(roll_expression(cur->left, false),
                             -roll_expression(cur->right, false));
            break;
      
        case OP_TIMES:
            sum = checked_multiplication(roll_expression(cur->left, false),
                                         roll_expression( cur->right, false));
            break;
      
        case OP_DIV:
            sum = (int)
            ceil((float)roll_expression(cur->left, false) /
                        roll_expression(cur->right, false));
            break;
      
        case OP_HIGH:
            sides       = roll_expression(cur->right->right->right, false);
            repetitions = roll_expression(cur->right->left, false);
            high        = roll_expression(cur->left, false);      

            /* array to store the results to sort */
            if (!(results = (int*) malloc(sizeof(int)*repetitions))) {
                output("out of memory", ERROR_CODE);
            }
      
            for(i=0; i<repetitions; i++) {
                Die die(sides);
                results[i] = die.roll();
            }

            qsort(results, repetitions, sizeof(int), &compare);

            for(i=(repetitions-high); i<repetitions; i++) {
                sum = checked_sum( sum, results[i] );
            }
      
            free(results);
            break;
      
        case OP_LOW:
            sides       = roll_expression(cur->right->right->right, false);
            repetitions = roll_expression(cur->right->left,  false);
            low         = roll_expression(cur->left, false);
      
            if (cur->right->left != NULL) {
                repetitions = roll_expression(cur->right->left, false);
            }
                  
            /* array to store the results to sort */
            if (!(results = (int*) malloc(sizeof(int)*repetitions))) {
                output("out of memory", ERROR_CODE);
            }
      
            for(i=0; i<repetitions; i++) {
                Die die(sides);
                results[i] = die.roll();
            }

            qsort(results, repetitions, sizeof(int), &compare);
      
            for(i=0; i<low; i++) {
                sum = checked_sum( sum, results[i] );
            }
      
            free(results);
            break;

        case OP_GT:
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
            
            while (tmp <= limit) {
                tmp = roll_expression(cur->left, false);
            }
            
            sum = checked_sum( sum, tmp );
            break;
      
        case OP_GE:
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
            
            while (tmp < limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
            break;
      
        case OP_LT:
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp >= limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
      
            break;
      
        case OP_LE:
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp > limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
            break;
        
        case OP_NE:
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp == limit) {
                tmp = roll_expression(cur->left, false);
                fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
                exit(EXIT_FAILURE);      
            }
        
            return return_value;
        }

        return_value = checked_sum(return_value, sum);

        if (print) {
            output(to_string(sum)+"\n");
        }

        cur = cur->next;
    }

    return return_value;
}