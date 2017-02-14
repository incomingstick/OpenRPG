/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <climits>
#include <cstring>
#include <cmath>
#include <cctype>

#include "utils.h"
#include "die.h"
#include "roll-parser.h"

using namespace std;

/**
  * @desc compares two values p1 and p2 as integers returning
  *     p1 > p2 = 1, p1 < p2 = -1, p1 = p2 = 0 
  * @param const void* p1 - first value to be compared
  * @param const void* p2 - second value to be compared
  * @return int - >  1, < -1, =  0
  */
int compare(const void* p1, const void* p2) {
    const int i1 = *((const int *)p1);
    const int i2 = *((const int *)p2);

    if (i1 > i2) return 1;
    else if (i1 < i2) return -1;
    else return 0;
}

/**
  * @desc creates a pointer to an empty parse_node
  * @return struct parse_node* - and empty parse_node
  */
struct parse_node* ExpressionTree::allocate_node() {
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

/**
  * @desc creates a parse_node with an op value of OP_NUMBER
  *     and a value of number
  * @param int number - number for the nodes value
  * @return struct parse_node* - pointer to the created parse_node
  */
struct parse_node* ExpressionTree::new_number(int number) {
    struct parse_node* node = allocate_node();
    
    node->op = OP_NUMBER;
    node->value = number;

    return node;
}

/**
  * @desc creates a pointer to a new parse_node that sits
  *     between the given left and right parse_nodes
  * @param unsigned short int op - the operator to be assigned to this parse_node 
  * @param struct parse_node* right - the node to the right of our new node
  * @param struct parse_node* left - the node to the left of our new node
  * @return struct parse_node* - a pointer to a node with the given op, left, and right
  */
struct parse_node* ExpressionTree::new_op (unsigned short int op, struct parse_node* left, struct parse_node* right) {
    struct parse_node* node = allocate_node();
    
    node->op = op;
    node->value = 0;
    node->left = left;
    node->right = right;
    
    return node;
  
}

/**
  * @desc creates a parse_node pointer with the OP_DIE op
  * @param struct parse_node* sides - the node to be placed to the right of our new node
  * @return struct parse_node* - a new node with op OP_DIE and sides on the right
  */
struct parse_node* ExpressionTree::new_die (struct parse_node* sides) {
    struct parse_node* node = allocate_node();
  
    node->op = OP_DIE;
    node->value = 0;
    node->right = sides;
    
    return node;
}

/**
  * @desc prints the character representation of a parse_nodes op value
  * @param struct parse_node* node - the node to print
  * @return Function return
  */
void print_node(struct parse_node* node, string pad) {
    switch(node->op) {
    case OP_NUMBER: output(pad +"number ("+ to_string(node->value) +")", VB_CODE); break;      
    case OP_DIE:   output(pad +"die", VB_CODE); break;
    case OP_PLUS:   output(pad +"+", VB_CODE); break;
    case OP_MINUS:  output(pad +"-", VB_CODE); break;
    case OP_TIMES:  output(pad +"*", VB_CODE); break;
    case OP_DIV:    output(pad +"/", VB_CODE); break;
    case OP_HIGH:   output(pad +"high", VB_CODE); break;
    case OP_LOW:    output(pad +"low", VB_CODE); break;
    case OP_GT:     output(pad +">", VB_CODE); break;
    case OP_GE:     output(pad +">=", VB_CODE); break;
    case OP_LT:     output(pad +"<", VB_CODE); break;
    case OP_LE:     output(pad +"<=", VB_CODE); break;
    case OP_NE:     output(pad +"!=", VB_CODE); break;
    case OP_REP:    output(pad +"rep", VB_CODE); break;
    default :       output(pad +"unknown node", VB_CODE); break;
    }
}

/**
  * @desc recursively prints to output a tree of parse_nodes starting with
  *     the top node node and taking precidence over the left node
  * @param struct parse_node* node - the top node of the tree to print
  * @param int - the amount of whitespace to indent the current node by
  */
void ExpressionTree::print_tree(struct parse_node* node, int indent) {
    int i;
    string pad("");

    for(i = 0; i < indent; i++) {
        pad += " ";
    }

    print_node(node, pad);

    output("\n", VB_FLAG);

    if(node->left != NULL) {
        print_tree(node->left, indent+1);
    }

    if(node->right != NULL) {
        print_tree(node->right, indent+1);
    }
}

/**
  * @desc parses the parse_node tree given the top node of the tree
  *     and prints the return value based on print bool
  * @param struct parse_node* node - the top node of the tree to parse
  * @param bool print - bool flag to print return value
  * @return Function return
  */
int ExpressionTree::parse_tree(struct parse_node* node, bool print) {
    int high;
    int i;
    int limit;
    int low;
    int repetitions;
    int sides;
    int tmp;
    int* results;

    int ret = 0;

    /* sets our current node to node */
    struct parse_node* cur = node;

    while (cur != NULL) {
        int sum = 0;

        switch(cur->op) {
        // number node
        case OP_NUMBER: {
            sum = cur->value;
        } break;

        // multiplication node
        case OP_TIMES: {
            sum = checked_multiplication(parse_tree(cur->left, false),
                                         parse_tree(cur->right, false));
        } break;

        // integer division node
        case OP_DIV: {
            sum = (int)
            ceil((float)parse_tree(cur->left, false) /
                        parse_tree(cur->right, false));
        } break;

        // n-sided die node
        case OP_DIE: {
            Die die(parse_tree(cur->right, false));
            sum = die.roll();
        } break;
      
        // addition node
        case OP_PLUS: {
            sum = checked_sum(parse_tree(cur->left, false),
                              parse_tree(cur->right, false));
        } break;
      
        // subtraction node
        case OP_MINUS: {
            sum = checked_sum(parse_tree(cur->left, false),
                             -parse_tree(cur->right, false));
        } break;
      
        // keep highest results node
        case OP_HIGH: {
            sides       = parse_tree(cur->right->right->right, false);
            repetitions = parse_tree(cur->right->left, false);
            high        = parse_tree(cur->left, false);      

            // array to store the results to sort
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
        
        // keep lowest resutls node
        case OP_LOW: {
            sides       = parse_tree(cur->right->right->right, false);
            repetitions = parse_tree(cur->right->left,  false);
            low         = parse_tree(cur->left, false);
      
            if (cur->right->left != NULL) {
                repetitions = parse_tree(cur->right->left, false);
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

        // keep results greater than
        case OP_GT: {
            limit = parse_tree(cur->right, false);      
            tmp   = parse_tree(cur->left,  false);
            
            while (tmp <= limit) {
                tmp = parse_tree(cur->left, false);
            }
            
            sum = checked_sum( sum, tmp );
        } break;
        
        // keep results greater or equal than
        case OP_GE: {
            limit = parse_tree(cur->right, false);      
            tmp   = parse_tree(cur->left,  false);
            
            while (tmp < limit) {
                tmp = parse_tree(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
        } break;
        
        // keep results less than
        case OP_LT: {
            limit = parse_tree(cur->right, false);      
            tmp   = parse_tree(cur->left,  false);
      
            while (tmp >= limit) {
                tmp = parse_tree(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
      
        } break;
        
        // keep results less or equal than
        case OP_LE: {
            limit = parse_tree(cur->right, false);      
            tmp   = parse_tree(cur->left,  false);
      
            while (tmp > limit) {
                tmp = parse_tree(cur->left, false);
            }
      
            sum = checked_sum( sum, tmp );
        } break;
        
        // keep results not equal to
        case OP_NE: {
            limit = parse_tree(cur->right, false);      
            tmp   = parse_tree(cur->left,  false);
      
            while (tmp == limit) {
                tmp = parse_tree(cur->left, false);
                fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
                exit(EXIT_FAILURE);      
            }
        
            return ret;
        } break;

        // number of rolls (repetitions)
        case OP_REP: {
            for (i = 0; i < parse_tree(cur->left, false); i++)
                sum = checked_sum(sum, parse_tree(cur->right, false));
        } break;

        default: {
            exit(output("got to default of parse_tree switch", EXIT_FAILURE));
        }
        }

        ret = checked_sum(ret, sum);

        if(print) output(to_string(sum)+"\n");

        cur = cur->next;    // move us to the next node in the tree
    }

    return ret;
}

/**
  * @desc reads in to the buffer bytes equal to maxBytesToRead
  *     begining with an offest equal to globalReadOffset
  *     and incremnting globalReadOffset by the number of bytes
  *     read.
  * @param char* buff - pointer to the buffer
  * @param int* numBytesRead - pointer to the number of bytes we have read
  * @param int maxBytesToRead - the maximum number of bytes to read
  * @return 0 - to signify success
  */
int ExpressionTree::parse_input_string(string* buff, int* numBytesRead, int maxBytesToRead) {
    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = inputString.length() - globalReadOffset;
    
    if(numBytesToRead > bytesRemaining) { numBytesToRead = bytesRemaining; }

    buff->clear();

    for(int i = 0; i < numBytesToRead; i++)
        buff->push_back(inputString[globalReadOffset+i]);
    
    *numBytesRead = numBytesToRead;
    globalReadOffset += numBytesToRead;
    
    return 0;
}

/**
  * @desc TODO parses the string held by the ExpressionTree
  */
void ExpressionTree::parse_expression(void) {
    string curParseString = "";

    int numBytesRead = 0;
    int numBytesToRead = 0;

    /* TODO we should scan the string to create the tree and parse out the expression */
    for(string::iterator it = inputString.begin(); it != inputString.end(); ++it) {
        char cur_ch = *it;
        if(isdigit(cur_ch)) {
            numBytesToRead++;
        } else if(!isspace(cur_ch)) {
            if(numBytesToRead > 0) {
                parse_input_string(&curParseString, &numBytesRead, numBytesToRead);
                output("number: "+curParseString+"\n");
                
                numBytesToRead = 0;
            }

            /* here we create a parse_node based on the current char */
            switch(cur_ch) {
            default: {
                output("char: "+ string(1, cur_ch) +"\n");
                globalReadOffset++;
            }
            }
        } else globalReadOffset++;

        if(it + 1 == inputString.end() && numBytesToRead > 0) {
            parse_input_string(&curParseString, &numBytesRead, numBytesToRead);
            output("number: "+curParseString+"\n");
                
            numBytesToRead = 0;
        }
    }
}

/**
  * @desc outputs an error with ERROR_CODE if there
  *     would be an addition overflow
  * @param int op1 - an integer to be added
  * @param int op2 - an integer to be added
  * @return int - op1 + op2
  */
int ExpressionTree::checked_sum(int op1, int op2) {
    if ((op2 > 0 && op1 > INT_MAX - op2) || (op2 < 0 && op1 < INT_MIN - op2))
        output("overflow", ERROR_CODE);
    
    return op1 + op2;
}

/**
  * @desc outputs an error with ERROR_CODE if there
  *     would be a multiplication overflow
  * @param int op1 - an integer to be multiplied
  * @param int op2 - an integer to be multiply by
  * @return int - op1 * op2
  */
int ExpressionTree::checked_multiplication(int op1, int op2) {
    int result = op1 * op2;
    if(op1 != 0 && result / op1 != op2 )
        output("overflow", ERROR_CODE);
    
    return result;
}