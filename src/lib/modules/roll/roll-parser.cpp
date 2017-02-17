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
#include <stack>

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
parse_node* ExpressionTree::allocate_node() {
    struct parse_node* node = (parse_node*) malloc(sizeof(struct parse_node));
    
    if(node == NULL) {
        output("out of memory", VB_CODE);
        exit(output("exiting with status "+to_string(EXIT_FAILURE), EXIT_FAILURE));
    }

    /* initialize default values */
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->op = 0;
    node->value = 0;
  
    return node;
}

/**
  * @desc creates a parse_node with an op value of OP_NUMBER
  *     and a value of number
  * @param int number - number for the nodes value
  * @return struct parse_node* - pointer to the created parse_node
  */
parse_node* ExpressionTree::new_number(int number) {
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
parse_node* ExpressionTree::new_op(unsigned short int op, struct parse_node* cur) {
    if(cur->op) {
        while(cur->parent) cur = cur->parent;
        cur->parent = allocate_node();
        cur->parent->left = cur;
        cur = cur->parent;
    }

    if(cur->left && op == OP_DIE) {
        cur->op = OP_REP;
        cur->right = allocate_node();
        cur->right->parent = cur;
        cur = cur->right;
    }
    
    cur->op = op;
    cur->right = allocate_node();
    cur->right->parent = cur;
    cur = cur->right;
    
    return cur;
}

/**
  * @desc creates a parse_node pointer with the OP_DIE op
  * @param struct parse_node* sides - the node to be placed to the right of our new node
  * @return struct parse_node* - a new node with op OP_DIE and sides on the right
  */
parse_node* ExpressionTree::new_die (struct parse_node* sides) {
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
string node_to_string(struct parse_node* node) {
    switch(node->op) {
    case OP_NUMBER: return to_string(node->value);      
    case OP_DIE:    return "die";
    case OP_PLUS:   return "+";
    case OP_MINUS:  return "-";
    case OP_TIMES:  return "*";
    case OP_DIV:    return "/";
    case OP_HIGH:   return "high";
    case OP_LOW:    return "low";
    case OP_GT:     return ">";
    case OP_GE:     return ">=";
    case OP_LT:     return "<";
    case OP_LE:     return "<=";
    case OP_NE:     return "!=";
    case OP_REP:    return "rep";
    default :       return "unknown node ("+ to_string(node->value) +", "+ to_string(node->op) +")";
    }
}

/**
  * @desc recursively prints to output a tree of parse_nodes starting with
  *     the top node node and taking precidence over the left node
  * @param struct parse_node* node - the top node of the tree to print
  * @param int - the amount of whitespace to indent the current node by
  */
void ExpressionTree::print_tree(struct parse_node* node, int indent, string pre) {
    int i;
    string pad("");

    for(i = 0; i < indent; i++) {
       pad += " ";
    }

    output(pad + pre + "(" + node_to_string(node) +")", VB_CODE);

    if(node->left != NULL) {
        print_tree(node->left, indent + 2, "left->");
    }

    if(node->right != NULL) {
        print_tree(node->right, indent + 2, "right->");
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
            exit(output("Implementation error: unkown IR node with code "+ to_string(cur->op) +"\n", EXIT_FAILURE));      
        }
    
        return ret;
    } break;

    // number of rolls (repetitions)
    case OP_REP: {
        int reps = parse_tree(cur->left, false);
        for (i = 0; i < reps; i++)
            sum = checked_sum(sum, parse_tree(cur->right, false));
    } break;

    default: {
        exit(output("got to default of parse_tree switch", EXIT_FAILURE));
    }
    }

    ret = checked_sum(ret, sum);

    if(print) output(to_string(sum)+"\n");

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
        buff->push_back(inputString[i + globalReadOffset]);
    
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

    struct parse_node* cur = head;

    /* Basic rules of a math expression parser (these WILL need improvement)
    1) If the current token is a '(', add a new node as the left
        child of the current node, and descend to the left child.

    2) If the current token is in the list ['+','-','/','*'],
        set value of the current node to the operator code
        representation of the current token. Add a new node as the
        right child of the current node and descend to the right child.

    3) If the current token is a number, set the root value of the
        current node to the number and return to the parent.

    4) If the current token is a ')', go to the parent of the current node.
    */

    /* TODO we should scan the string to create the tree and parse out the expression */
    for(string::iterator it = inputString.begin(); it != inputString.end(); ++it) {
        char cur_ch = *it;
        if(isdigit(cur_ch)) {
            numBytesToRead++;
        } else if(!isspace(cur_ch)) {
            /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
            if(numBytesToRead > 0) {
                parse_input_string(&curParseString, &numBytesRead, numBytesToRead);
                output("number: "+curParseString, VB_CODE);

                cur->value = stoi(curParseString);
                cur->op = OP_NUMBER;

                if(cur->parent == NULL) {
                    cur->parent = allocate_node();
                    cur->parent->left = cur;
                }
                
                cur = cur->parent;

                numBytesToRead = 0;
            }

            switch(cur_ch) {
            /* 1) If the current token is a '(', add a new node as the left
                child of the current node, and descend to the left child. */
            case '(': {
                struct parse_node* left = allocate_node();
                left->parent = cur;
                cur->left = left;
                cur = cur->left;
            } break;

            /* 2) If the current token is in the list ['+','-','/','*'],
                set value of the current node to the operator code
                representation of the current token. Add a new node as the
                right child of the current node and descend to the right child. */
            case '+': {
                cur = new_op(OP_PLUS, cur);
            } break;

            case '-': {
                cur = new_op(OP_MINUS, cur);
            } break;

            case '*': {
                cur = new_op(OP_TIMES, cur);
            } break;

            case '/': {
                cur = new_op(OP_DIV, cur);
            } break;

            case 'd': {
                cur = new_op(OP_DIE, cur);
            } break;

            /* 4) If the current token is a ')', go to the parent of the current node. */
            case ')': {
                if(cur->parent != NULL) cur = cur->parent;
            } break;

            default: {
                /* 
                 * Default case for this scanner.
                 * This set of characters will include all
                 * charcters except:
                 *  ['+','-','/','*', '()', '0-9']
                 */
            }
            }
            
            output("char: "+ string(1, cur_ch), VB_CODE);

            globalReadOffset++;  
        } else {
            /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
            if(numBytesToRead > 0) {
                parse_input_string(&curParseString, &numBytesRead, numBytesToRead);
                output("number: "+curParseString, VB_CODE);
                
                cur->value = stoi(curParseString);
                cur->op = OP_NUMBER;

                if(cur->parent == NULL) {
                    cur->parent = allocate_node();
                    cur->parent->left = cur;
                }
                
                cur = cur->parent;

                numBytesToRead = 0;
            }

            globalReadOffset++;
        }

        /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
        if(it + 1 == inputString.end() && numBytesToRead > 0) {
            parse_input_string(&curParseString, &numBytesRead, numBytesToRead);
            output("number: "+curParseString, VB_CODE);
            
            cur->value = stoi(curParseString);
            cur->op = OP_NUMBER;

            if(cur->parent == NULL) {
                cur->parent = allocate_node();
                cur->parent->left = cur;
            }
                
            cur = cur->parent;

            numBytesToRead = 0;
        }
    }
    while(head->parent) head = head->parent;    // TODO make our head tracking more efficient

    print_tree(head, 0);

    if(parse_tree(head, true) != 0);
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