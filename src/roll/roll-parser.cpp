/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <climits>
#include <string>

#include "roll/roll-parser.h"

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
    struct parse_node* node = new parse_node;
    
    if(node == NULL) {
        printf("out of memory");
        exit(EXIT_FAILURE);
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
  * @desc sets cur to a parse_node with an op value of OP_NUMBER and a value of
  *     read from the input string and return the parent of cur
  * @param struct parse_node* cur - the current node
  * @param int* numBytesToRead - the number of bytes to read from the input string
  * @return struct parse_node* - pointer to the parent of cur
  */
struct parse_node* ExpressionTree::new_number(struct parse_node* cur, int
					      * numBytesToRead) {
    string curParseString = "";

    int numBytesRead = 0;

    parse_input_string(&curParseString, &numBytesRead, *numBytesToRead);
            
    cur->value = stoi(curParseString);
    cur->op = OP_NUMBER;

    if(cur->parent == NULL && (size_t) numBytesRead != inputString.length()) {
        cur->parent = allocate_node();
        cur->parent->left = cur;
    }
        
    cur = cur->parent;

    *numBytesToRead = 0;
    
    return cur;
}

/**
  * @desc sets cur to a parse_node with an op value of op and a new node as the right
  *     child of the cur node and returns the right child
  * @param struct parse_node* cur - the current node
  * @param unsigned short int op - the operator to be assigned to the cur parse_node 
  * @return struct parse_node* - a pointer to the right child of cur
  */
parse_node* ExpressionTree::new_op(struct parse_node* cur, unsigned short int op) {
    if(cur->op) {
        while(cur->parent) cur = cur->parent;
        cur->parent = allocate_node();
        cur->parent->left = cur;
        cur = cur->parent;
    }
    
    cur->op = op;
    cur->right = allocate_node();
    cur->right->parent = cur;
    cur = cur->right;
    
    return cur;
}

/**
  * @desc sets cur to a parse_node with an op value of op and a new node as the right
  *     child of the cur node and returns the right child
  * @param struct parse_node* cur - the current node
  * @return struct parse_node* - a pointer to the right child of cur
  */
parse_node* ExpressionTree::new_die(struct parse_node* cur) {
    if(cur->op) {
        while(cur->parent) cur = cur->parent;
        cur->parent = allocate_node();
        cur->parent->left = cur;
        cur = cur->parent;
    }

    if(cur->left) {
        cur->op = OP_REP;
        cur->right = allocate_node();
        cur->right->parent = cur;
        cur = cur->right;
    }
    
    cur->op = OP_DIE;
    cur->right = allocate_node();
    cur->right->parent = cur;
    cur = cur->right;
    
    return cur;
}

/**
  * @desc prints the character representation of a parse_nodes op value
  * @param struct parse_node* node - the node to print
  * @return Function return
  */
string node_to_string(struct parse_node* node) {
    switch(node->op) {
    case OP_NUMBER: return std::to_string(node->value);      
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
    default :       return "unknown node ("+ std::to_string(node->value) +", "+ std::to_string(node->op) +")";
    }
}

/**
  * @desc recursively returns a string of the tree of parse_nodes starting with
  *     the top node node and taking precidence over the left node and ending
  *     with the char '\n'
  * @param struct parse_node* node - the top node of the tree to print
  * @param int - the amount of whitespace to indent the current node by
  * @return string - a string of the tree of parse_nodes
  */
string ExpressionTree::tree_string(struct parse_node* node, int indent, string pre) {
    int i;
    string pad("");
    string ret("");

    for(i = 0; i < indent; i++) pad += " ";

    ret = pad + pre + "(" + node_to_string(node) +")\n";

    if(node->left != NULL)  ret += tree_string(node->left, indent + 2, "left->");
    if(node->right != NULL) ret += tree_string(node->right, indent + 2, "right->");

    return ret;
}

/**
  * @desc parses the parse_node tree given the top node of the tree
  *     and returns the end result of the expression
  * @param struct parse_node* node - the top node of the tree to parse
  * @return int - the end result of the expression
  */
int ExpressionTree::parse_tree(struct parse_node* node) {
    int high;
    int i;
    int limit;
    int low;
    int repetitions;
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
        sum = checked_multiplication(parse_tree(cur->left),
                                     parse_tree(cur->right));
    } break;

    // integer division node
    case OP_DIV: {
        sum = (int)
        ceil((float)parse_tree(cur->left) /
                    parse_tree(cur->right));
    } break;

    // n-sided die node
    case OP_DIE: {
        Die die(parse_tree(cur->right));
        sum = die.roll();
    } break;
      
    // addition node
    case OP_PLUS: {
        sum = checked_sum(parse_tree(cur->left),
                          parse_tree(cur->right));
    } break;
      
    // subtraction node
    case OP_MINUS: {
        sum = checked_sum(parse_tree(cur->left),
                         -parse_tree(cur->right));
    } break;
      
    // keep highest results node
    case OP_HIGH: {
        repetitions = parse_tree(cur->left->left);
        high        = parse_tree(cur->right);      

        // array to store the results to sort
        if (!(results = new int[repetitions])) {
            printf("out of memory");
        }
      
        for(i = 0; i < repetitions; i++) {
            results[i] = parse_tree(cur->left->right);
        }

        qsort(results, repetitions, sizeof(int), &compare);

        for(i = (repetitions - high); i < repetitions; i++) {
            sum = checked_sum(sum, results[i]);
        }
      
        delete[] results;
    } break;
        
    // keep lowest resutls node
    case OP_LOW: {
        repetitions = parse_tree(cur->left->left);
        low         = parse_tree(cur->right);
                  
        /* array to store the results to sort */
        if (!(results = new int[repetitions])) {
            printf("out of memory");
        }
      
        for(i = 0; i < repetitions; i++) {
            results[i] = parse_tree(cur->left->right);
        }

        qsort(results, repetitions, sizeof(int), &compare);
      
        for(i = 0; i < low; i++) {
            sum = checked_sum(sum, results[i]);
        }
      
        delete[] results;
    } break;

    // keep results greater than
    case OP_GT: {
        limit = parse_tree(cur->right);      
        tmp   = parse_tree(cur->left);
            
        while (tmp <= limit) {
            tmp = parse_tree(cur->left);
        }
            
        sum = checked_sum(sum, tmp);
    } break;

    // keep results greater or equal than
    case OP_GE: {
        limit = parse_tree(cur->right);      
        tmp   = parse_tree(cur->left);
        
        while (tmp < limit) {
            tmp = parse_tree(cur->left);
        }
    
        sum = checked_sum( sum, tmp );
    } break;
        
    // keep results less than
    case OP_LT: {
        limit = parse_tree(cur->right);      
        tmp   = parse_tree(cur->left);
    
        while (tmp >= limit) {
            tmp = parse_tree(cur->left);
        }
    
        sum = checked_sum(sum, tmp);
    
    } break;
    
    // keep results less or equal than
    case OP_LE: {
        limit = parse_tree(cur->right);      
        tmp   = parse_tree(cur->left);
    
        while (tmp > limit) {
            tmp = parse_tree(cur->left);
        }
    
        sum = checked_sum(sum, tmp);
    } break;
    
    // keep result not equal to
    case OP_NE: {
        limit = parse_tree(cur->right);      
        tmp   = parse_tree(cur->left);
    
        while (tmp == limit) {
            tmp = parse_tree(cur->left);      
        }
    
        return ret;
    } break;

    // number of rolls (repetitions)
    case OP_REP: {
        int reps = parse_tree(cur->left);
        for (i = 0; i < reps; i++)
            sum = checked_sum(sum, parse_tree(cur->right));
    } break;

    default: {
        fprintf(stderr, "Invalid option - %c\n", cur->op);
        
        exit(EXIT_FAILURE);
    }
    }

    ret = checked_sum(ret, sum);

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

// TODO ensure integrity of this string before
static bool is_expression_valid(const std::string exp) {
    return true;
}

/**
 * @desc sets the input string to be scanned and parsed equal to the string exp
 * @param const std::string exp - the string to become the input string
 */
bool ExpressionTree::set_expression(const std::string exp) {
    if(!is_expression_valid(exp)) return false;
    
    inputString = exp;

    return build_expression_tree();
}
    

/**
  * @desc scans the string held by the ExpressionTree and
  * creates a binary tree to be parsed out
  *
  * TODO: Improve error reporting to point to the exact character
  * in the string that is considered invalid, i.e mimic GCC\LLDB
  * error reporting
  * 
  * example:
  *      $ roll character
  *      Invalid character 'c' found in expression:
  *                 character
  *                 ^~~~~~~~~
  */
bool ExpressionTree::build_expression_tree(void) {
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
    for(auto it = inputString.begin(); it != inputString.end(); ++it) {
        auto cur_ch = *it;
        if(isdigit(cur_ch)) {
            numBytesToRead++;
        } else if(!isspace(cur_ch)) {
            /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
            if(numBytesToRead > 0)
                cur = new_number(cur, &numBytesToRead);

            switch(cur_ch) {
            /* 1) If the current token is a '(', '[', or '{', add a new node as the left
                child of the current node, and descend to the left child. */
            case '{': {
                cur = new_op(cur, OP_REP);
            } // we want this to cascade in to '('
            case '[':
            case '(': {
                cur->left = allocate_node();
                cur->left->parent = cur;
                cur = cur->left;
            } break;

            /* 2) If the current token is in the list, set value of the current
                node to the operator code representation of the current token.
                Add a new node as the right child of the current node and descend
                to the right child. */
            case '+': {
                cur = new_op(cur, OP_PLUS);
            } break;

            case '-': {
                cur = new_op(cur, OP_MINUS);
            } break;

            case '*': {
                cur = new_op(cur, OP_TIMES);
            } break;

            case '/': {
                cur = new_op(cur, OP_DIV);
            } break;

            case 'd': {
                cur = new_die(cur);
            } break;

            // TODO generate a set (vector/array) of numbers
            case 'h': {
                cur = new_op(cur, OP_HIGH);
            } break;

            // TODO generate a set (vector/array) of numbers
            case 'l': {
                cur = new_op(cur, OP_LOW);
            } break;

            case '>': {
                cur = new_op(cur, OP_GT);
            } break;

            case '<': {
                cur = new_op(cur, OP_LT);
            } break;

            case '!': {
                cur = new_op(cur, OP_NE);
            } break;

            case '=': {
                if(cur->parent) {
                    switch(cur->parent->op) {
                    case OP_GT: {
                        cur->parent->op = OP_GE;
                    } break;

                    case OP_LT: {
                        cur->parent->op = OP_LE;
                    } break;

                    default: {
                        fprintf(stderr, "Invalid character %c found in expression\n", cur_ch);
                        return false;
                    }
                    }
                }
            } break;

            /* 4) If the current token is a ')', ']', or '}, go to the parent of the current node. */
            case '}':
            case ']':
            case ')': {
                if(cur->parent != NULL) cur = cur->parent;
            } break;

            default: {
                /* 
                 * Default case for this scanner.
                 * This set of characters will include all
                 * charcters not included above
                 */
                fprintf(stderr, "Invalid character %c found in expression\n", cur_ch);
                
                return false;
            }
            }

            globalReadOffset++;  
        } else {
            /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
            if(numBytesToRead > 0)
                cur = new_number(cur, &numBytesToRead);

            globalReadOffset++;
        }

        /* 3) If the current token is a number, set the root value of the
                current node to the number and return to the parent. */
        if(it + 1 == inputString.end() && numBytesToRead > 0)
            cur = new_number(cur, &numBytesToRead);
    }
    while(head->parent) head = head->parent;    // TODO make our head tracking more efficient

    return true;
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
        printf("overflow");
    
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
        printf("overflow");
    
    return result;
}
