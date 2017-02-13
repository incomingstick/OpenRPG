/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
/*
TODO we will need to intergrate this in to our roll.cpp file to
be used to interface with the die class and anything else we would
like to do in this parser.
*/
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
        case OP_NUMBER: {
            sum = cur->value;
        } break;

        case OP_REP: {
            for (i = 0; i < roll_expression(cur->left, false); i++)
                sum = checked_sum(sum, roll_expression(cur->right, false));
        } break;
      
        case OP_DICE: {
            Die die(roll_expression(cur->right, false));
            sum = die.roll();
        } break;
      
        case OP_PLUS: {
            sum = checked_sum(roll_expression(cur->left, false),
                              roll_expression(cur->right, false));
        } break;
      
        case OP_MINUS: {
            sum = checked_sum(roll_expression(cur->left, false),
                             -roll_expression(cur->right, false));
        } break;
      
        case OP_TIMES: {
            sum = checked_multiplication(roll_expression(cur->left, false),
                                         roll_expression( cur->right, false));
        } break;
      
        case OP_DIV: {
            sum = (int)
            ceil((float)roll_expression(cur->left, false) /
                        roll_expression(cur->right, false));
        } break;
      
        case OP_HIGH: {
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
        } break;
      
        case OP_LOW: {
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
        } break;

        case OP_GT: {
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
            
            while (tmp <= limit) {
                tmp = roll_expression(cur->left, false);
            }
            
            sum = checked_sum( sum, tmp );
        } break;
      
        case OP_GE: {
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
            
            while (tmp < limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
        } break;
      
        case OP_LT: {
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp >= limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
      
        } break;
      
        case OP_LE: {
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp > limit) {
                tmp = roll_expression(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
        } break;
        
        case OP_NE: {
            limit = roll_expression(cur->right, false);      
            tmp   = roll_expression(cur->left,  false);
      
            while (tmp == limit) {
                tmp = roll_expression(cur->left, false);
                fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
                exit(EXIT_FAILURE);      
            }
        
            return return_value;
        } break;

        default: {
            exit(output("got to default of roll_expression switch", EXIT_FAILURE));
        }
        }

        return_value = checked_sum(return_value, sum);

        if (print) {
            output(to_string(sum)+"\n");
        }

        cur = cur->next;
    }

    return return_value;
}