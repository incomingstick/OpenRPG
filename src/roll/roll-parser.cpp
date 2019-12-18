/*
roll - roll-parser.cpp
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <climits>
#include <string>

#include "core/config.h"
#include "roll/roll-parser.h"

using namespace std;

namespace ORPG {
    namespace Roll {
        /**
         * @desc prints the current compiled version
         * @return void - always exits with status EXIT_SUCCESS
         */
        void print_version_flag() {
            fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        /**
         * @desc prints the help and usage menu
         * @return void - always exits with status EXIT_SUCCESS
         */
        void print_help_flag() {
            fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: roll [options] XdY [+|-] AdB [+|-] N [...]\n"
                        "\t-h --help                   Print this help screen\n"
                        "\t-v --verbose                Verbose program output\n"
                        "\t-V --version                Print version info\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
            exit(EXIT_SUCCESS);
        }

        /**
         * @desc prints the current compiled version
         * @return void - always exits with status EXIT_SUCCESS
         */
        void print_basic_version() {
            fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n",
                stdout);
        }

        /**
         * @desc prints the help and usage menu
         * @return void - always exits with status EXIT_SUCCESS
         */
        void print_basic_help() {
            fputs("roll (openrpg) " VERSION " - " COPYRIGHT "\n"
                "OpenRPG Software License - Version 1.0 - February 10th, 2017 <https://openrpg.io/about/license/>\n"
                "This is free software: you are free to change and redistribute it.\n"
                "There is NO WARRANTY, to the extent permitted by law.\n\n"
                "Usage: roll [options] XdY [+|-] AdB [+|-] N [...]\n"
                "\n"
                "Long options may not be passed with a single dash.\n"
                "OpenRPG home page: < https://www.openrpg.io >\n"
                "Report bugs to: < https://github.com/incomingstick/OpenRPG/issues >\n"
                "See 'man name-generator' for more information [TODO add man pages].\n",
                stdout);
        }
    }

    /**
     * @desc compares two values p1 and p2 as integers returning
     *     p1 > p2 = 1, p1 < p2 = -1, p1 = p2 = 0 
     * @param const void* p1 - first value to be compared
     * @param const void* p2 - second value to be compared
     * @return int - >  1, < -1, =  0
     */
    int compare(const void* p1, const void* p2) {
        auto i1 = *((const int *)p1);
        auto i2 = *((const int *)p2);

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
     * @desc sets curr to a parse_node with an op value of OP_NUMBER and a value of
     *     read from the input string and return the parent of curr
     * @param struct parse_node* curr - the current node
     * @param int* numBytesToRead - the number of bytes to read from the input string
     * @return struct parse_node* - pointer to the parent of curr
     */
    struct parse_node* ExpressionTree::new_number(struct parse_node* curr, int
                            * numBytesToRead) {
        string currParseString = "";
        int numBytesRead = 0;

        parse_input_string(&currParseString, &numBytesRead, *numBytesToRead);

        if(!curr->left) {
            curr->left = allocate_node();
            curr->left->parent = curr;
            curr = curr->left;
        } else if(!curr->right) {
            curr->right = allocate_node();
            curr->right->parent = curr;
            curr = curr->right;
        }
                
        curr->value = stoi(currParseString);
        curr->op = OP_NUMBER;


        if(curr->parent == NULL && (size_t)numBytesRead != inputString.length()) {
            curr->parent = allocate_node();
            curr->parent->left = curr;
        }
            
        curr = curr->parent;

        *numBytesToRead = 0;
        
        return curr;
    }

    /**
     * @desc sets curr to a parse_node with an op value of op and a new node as the right
     *     child of the curr node and returns the right child
     * @param struct parse_node* curr - the current node
     * @param short int op - the operator to be assigned to the curr parse_node 
     * @return struct parse_node* - a pointer to the right child of curr
     */
    parse_node* ExpressionTree::new_op(struct parse_node* curr, short int op) {
        if(curr->op) {
            while(curr->parent &&
                curr->parent->op != OP_EXPR) {
                curr = curr->parent;
            }

            if(!curr->parent) {
                curr->parent = allocate_node();
                curr->parent->left = curr;
                curr = curr->parent;
            } else if(curr->parent->op == OP_EXPR) {
                auto swapAddr = curr->parent;
                curr->parent = allocate_node();
                curr->parent->parent = swapAddr;
                curr->parent->parent->left = curr->parent;
                curr->parent->parent->right = curr->parent;
                curr->parent->left = curr;
                curr = curr->parent;
            }
        }
        
        curr->op = op;
        curr->right = allocate_node();
        curr->right->parent = curr;
        curr = curr->right;
        
        return curr;
    }

    /**
     * @desc sets curr to a parse_node with an op value of op and a new node as the right
     *     child of the curr node and returns the right child
     * @param struct parse_node* curr - the current node
     * @return struct parse_node* - a pointer to the right child of curr
     */
    parse_node* ExpressionTree::new_die(struct parse_node* curr) {
        if(curr->op) {
            while(curr->parent && curr->parent->op != OP_EXPR) curr = curr->parent;
            if(curr->op != OP_EXPR) {
                curr->parent = allocate_node();
                curr->parent->left = curr;
                curr = curr->parent;
            } else if(curr->op == OP_EXPR) {
                auto swapAddr = curr->parent;
                curr->parent = allocate_node();
                curr->parent->parent = swapAddr;
                curr = curr->parent;
            }
        }

        if(!curr->left) {
            curr->left = allocate_node();
            curr->left->parent = curr;
            curr->left->op = OP_NUMBER;
            curr->left->value = 1;
        }
        
        curr->op = OP_DIE;
        
        return curr;
    }

    /**
     * @desc Sets node to an error state. The node's children and parent will been cleared
     * and the value will be set to 0. The op code will be set to OP_ERR.
     * @param struct parse_node* curr - the node to set error state
     * @return struct parse_node* - a pointer to the node
     */
    parse_node* ExpressionTree::node_error(struct parse_node* node) {
        if(node) {
            node->left = NULL;
            node->right = NULL;
            node->parent = NULL;
            node->value = 0;
            node->op = OP_ERR;
        } else {
            node = allocate_node();
            node->op = OP_ERR;
        }
        return node;
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
        case OP_MOD:    return "%";
        case OP_HIGH:   return "high";
        case OP_LOW:    return "low";
        case OP_GT:     return ">";
        case OP_GE:     return ">=";
        case OP_LT:     return "<";
        case OP_LE:     return "<=";
        case OP_NE:     return "!=";
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
        int size;
        int reps;
        int tmp;
        int* results;
        Die* die;

        int ret = 0;

        /* sets our current node to node */
        auto curr = node;

        int sum = 0;

        if(!curr || (!curr->op && !curr->value)) {
            return 0;
        }

        switch(curr->op) {
        // error node
        case OP_ERR: {
            return 0;
        } break;

        // number node
        case OP_NUMBER: {
            sum = curr->value;
        } break;

        // n-sided die node
        case OP_DIE: {
            reps = curr->left ? parse_tree(curr->left) : 1;
            size = parse_tree(curr->right);

            if(reps == 0) {
                break;
            }

            if(size < 2 && size > -2) {
                sum = checked_sum(sum, size);
                break;
            }

            die = new Die(size); 
            
            for(i = 0; i < reps; i++) {
                sum = checked_sum(sum, die->roll());
            }
            
            delete[] die;
        } break;

        // multiplication node
        case OP_TIMES: {
            sum = checked_multiplication(parse_tree(curr->left),
                                         parse_tree(curr->right));
        } break;

        // integer division node
        case OP_DIV: {
            sum = (int)
            ceil((float)parse_tree(curr->left) /
                        parse_tree(curr->right));
        } break;
        
        // addition node
        case OP_PLUS: {
            sum = checked_sum(parse_tree(curr->left),
                              parse_tree(curr->right));
        } break;
        
        // subtraction node
        case OP_MINUS: {
            sum = checked_sum(parse_tree(curr->left),
                             -parse_tree(curr->right));
        } break;

        // modulo node
        case OP_MOD: {
            sum = parse_tree(curr->left) % parse_tree(curr->right);
        } break;
        
        // keep highest results node
        case OP_HIGH: {
            reps = parse_tree(curr->left->left);
            high = parse_tree(curr->right);
            size = parse_tree(curr->left->right);

            if(reps == 0) {
                break;
            }

            if(size < 2 && size > -2) {
                sum = checked_sum(sum, size);
                break;
            }

            // array to store the results to sort
            if (!(results = new int[reps])) {
                printf("out of memory");
                break;
            }
        
            Die* die = new Die(size);

            for(i = 0; i < reps; i++) {
                results[i] = die->roll();
            }

            delete[] die;

            qsort(results, reps, sizeof(int), &compare);

            for(i = (reps - high); i < reps; i++) {
                sum = checked_sum(sum, results[i]);
            }
        
            delete[] results;
        } break;
            
        // keep lowest resutls node
        case OP_LOW: {
            reps    = parse_tree(curr->left->left);
            low     = parse_tree(curr->right);
            size    = parse_tree(curr->left->right);

            if(reps == 0) {
                break;
            }

            if(size < 2 && size > -2) {
                sum = checked_sum(sum, size);
                break;
            }
                    
            /* array to store the results to sort */
            if (!(results = new int[reps])) {
                printf("out of memory");
                break;
            }
        
            Die* die = new Die(size);

            for(i = 0; i < reps; i++) {
                results[i] = die->roll();
            }

            delete[] die;

            qsort(results, reps, sizeof(int), &compare);
        
            for(i = 0; i < low; i++) {
                sum = checked_sum(sum, results[i]);
            }
        
            delete[] results;
        } break;

        // keep results greater than
        case OP_GT: {
            limit = parse_tree(curr->right);      
            tmp   = parse_tree(curr->left);
                
            while (tmp <= limit) {
                tmp = parse_tree(curr->left);
            }
                
            sum = checked_sum(sum, tmp);
        } break;

        // keep results greater or equal than
        case OP_GE: {
            limit = parse_tree(curr->right);      
            tmp   = parse_tree(curr->left);
            
            while (tmp < limit) {
                tmp = parse_tree(curr->left);
            }
        
            sum = checked_sum( sum, tmp );
        } break;
            
        // keep results less than
        case OP_LT: {
            limit = parse_tree(curr->right);      
            tmp   = parse_tree(curr->left);
        
            while (tmp >= limit) {
                tmp = parse_tree(curr->left);
            }
        
            sum = checked_sum(sum, tmp);
        
        } break;
        
        // keep results less or equal than
        case OP_LE: {
            limit = parse_tree(curr->right);      
            tmp   = parse_tree(curr->left);
        
            while (tmp > limit) {
                tmp = parse_tree(curr->left);
            }
        
            sum = checked_sum(sum, tmp);
        } break;
        
        // keep result not equal to
        case OP_NE: {
            limit = parse_tree(curr->right);      
            tmp   = parse_tree(curr->left);
        
            while (tmp == limit) {
                tmp = parse_tree(curr->left);      
            }
        
            return ret;
        } break;

        default: {
            if(Core::VB_FLAG) fprintf(stderr, "Expression Parse Error: Invalid option - %c\n", curr->op);
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

    // TODO ensure integrity of this string before we actually allow rolling
    bool ExpressionTree::is_expression_valid(const std::string exp) {
        return true;
    }

    /**
     * @desc sets the input string to be scanned and parsed equal to the string exp
     * and resets the globalReadOffset
     * @param const std::string exp - the string to become the input string
     */
    bool ExpressionTree::set_expression(const std::string exp) {
        if(!is_expression_valid(exp)) return false;
        
        inputString = exp;
        globalReadOffset = 0;
        head = allocate_node();

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

        auto curr = head;

        /**
         * Basic rules of a math expression parser (these WILL need improvement)
         *  1) If the current token is a '(', add a new node as the left
         *      child of the current node, and descend to the left child.
         * 
         *  2) If the current token is in the list ['+','-','/','*'],
         *      set value of the current node to the operator code
         *      representation of the current token. Add a new node as the
         *      right child of the current node and descend to the right child.
         * 
         *  3) If the current token is a number, set the root value of the
         *      current node to the number and return to the parent.
         * 
         *  4) If the current token is a ')', go to the parent of the current node.
         * 
         * FIXME(incomingstick): Currently an expression could be opened with a '(' and
         * closed with a ']' or '}' or vice versa
         **/
        for(auto it = inputString.begin(); it != inputString.end(); ++it) {
            auto curr_ch = *it;
            if(isdigit(curr_ch)) {
                numBytesToRead++;
            } else if(!isspace(curr_ch)) {
                /* 3) If the current token is a number, set the root value of the
                    current node to the number and return to the parent. */
                if(numBytesToRead > 0) {
                    curr = new_number(curr, &numBytesToRead);
                }

                switch(curr_ch) {
                /* 1) If the current token is a '(', '[', or '{', add a new node as the left
                    child of the current node, and descend to the left child. */
                case '{':
                case '[':
                case '(': {
                    if(curr->op) {
                        /**
                         * If we currently have an op, try and create a new expression node as child.
                         * An expression node has a single child that should be thought of as it's own
                         * expression tree
                         **/
                        if(!curr->left) {
                            curr->left = allocate_node();
                            curr->left->parent = curr;
                            curr = curr->left;
                            curr->op = OP_EXPR;
                        } else if(!curr->right) {
                            curr->right = allocate_node();
                            curr->right->parent = curr;
                            curr = curr->right;
                            curr->op = OP_EXPR;
                        }

                        // If we successfully made the OP_EXPR node, create the left child and move to it
                        if(curr->op == OP_EXPR) {
                            curr->left = allocate_node();
                            curr->left->parent = curr;
                            curr->right = curr->left;
                            curr = curr->left;
                        }
                    }
                } break;

                /* 2) If the current token is in the list, set value of the current
                    node to the operator code representation of the current token.
                    Add a new node as the right child of the current node and descend
                    to the right child. */
                case '+': {
                    curr = new_op(curr, OP_PLUS);
                } break;

                case '-': {
                    curr = new_op(curr, OP_MINUS);
                } break;

                case '*': {
                    curr = new_op(curr, OP_TIMES);
                } break;

                case '/': {
                    curr = new_op(curr, OP_DIV);
                } break;

                case '%': {
                    curr = new_op(curr, OP_MOD);
                } break;

                case 'd': {
                    curr = new_die(curr);
                } break;

                // TODO generate a set (vector/array) of numbers
                case 'h': {
                    curr = new_op(curr, OP_HIGH);
                } break;

                // TODO generate a set (vector/array) of numbers
                case 'l': {
                    curr = new_op(curr, OP_LOW);
                } break;

                case '>': {
                    curr = new_op(curr, OP_GT);
                } break;

                case '<': {
                    curr = new_op(curr, OP_LT);
                } break;

                case '!': {
                    curr = new_op(curr, OP_NE);
                } break;

                case '=': {
                    if(curr->parent) {
                        switch(curr->parent->op) {
                        case OP_GT: {
                            curr->parent->op = OP_GE;
                        } break;

                        case OP_LT: {
                            curr->parent->op = OP_LE;
                        } break;

                        default: {
                            if(Core::VB_FLAG) fprintf(stderr, "Expression parse error: Invalid character %c found in expression\n", curr_ch);
                            // Set the head to a error
                            head = node_error(head);
                            return false;
                        }
                        }
                    }
                } break;

                /* 4) If the current token is a ')', ']', or '}, go to the parent of the current node tree */
                case '}':
                case ']':
                case ')': {
                    if(curr->parent) {
                        // ensure that if the currrent node is empty, that we bring up its child
                        // if our current node's op and value are empty, we consider it an empty node
                        if(!curr->op && !curr->value) {
                            // check if our current node has a left or right child, and set that childs
                            // parent to our current parent
                            if(curr->left) {
                                curr->left->parent = curr->parent;

                                // if we are the left or right of our parent, set our child to that node
                                if(curr->parent->left == curr)
                                    curr->parent->left = curr->left;
                                else if(curr->parent->right == curr)
                                    curr->parent->right = curr->left;
                            } else if(curr->right) {
                                curr->right->parent = curr->parent;

                                // if we are the left or right of our parent, set our child to that node
                                if(curr->parent->left == curr)
                                    curr->parent->left = curr->right;
                                else if(curr->parent->right == curr)
                                    curr->parent->right = curr->right;
                            }

                            curr = curr->parent;
                        }

                        // we are leaving the current expression so lets remove the OP_EXPR node by setting
                        // the subtree's head as this node
                        if(curr->parent && curr->parent->op == OP_EXPR) {
                            if(curr->parent->parent->left == curr->parent)
                                curr->parent->parent->left = curr;
                            else if(curr->parent->parent->right == curr->parent)
                                curr->parent->parent->right = curr;
                            curr->parent = curr->parent->parent;
                        }
                    }
                } break;

                default: {
                    /* 
                    * Default case for this scanner.
                    * This set of characters will include all
                    * charcters not included above
                    */
                    if(Core::VB_FLAG) fprintf(stderr, "Expression parse error: Invalid character %c found in expression\n", curr_ch);
                    head = node_error(head);
                    return false;
                }
                }

                globalReadOffset++;  
            } else {
                /* 3) If the current token is a number, set the root value of the
                    current node to the number and return to the parent. */
                if(numBytesToRead > 0){
                    curr = new_number(curr, &numBytesToRead);
                    // if our current node's op and value are empty, we consider it an empty node
                    if(!curr->op && !curr->value) {
                        // check if our current node has a left or right child, and set that childs
                        // parent to our current parent
                        if(curr->left) {
                            curr->left->parent = curr->parent;

                            // if we are the left or right of our parent, set our child to that node
                            if(curr->parent->left == curr)
                                curr->parent->left = curr->left;
                            else if(curr->parent->right == curr)
                                curr->parent->right = curr->left;
                        } else if(curr->right) {
                            curr->right->parent = curr->parent;

                            // if we are the left or right of our parent, set our child to that node
                            if(curr->parent->left == curr)
                                curr->parent->left = curr->right;
                            else if(curr->parent->right == curr)
                                curr->parent->right = curr->right;
                        }

                        curr = curr->parent;
                    }
                }

                globalReadOffset++;
            }

            /* 3) If the current token is a number, and we are the end of the string,
                set the root value of the current node to the number and return to the parent. */
            if(it + 1 == inputString.end() && numBytesToRead > 0) {
                curr = new_number(curr, &numBytesToRead);
                if(!curr->op && !curr->value) {
                    // because this is the last item, we can assume it was placed
                    // to the left of our current node
                    curr->left->parent = curr->parent;

                    // if our parent exists, set our child to our current position relative to our parent
                    // otherwise we assume our child should become the head node
                    if(curr->parent && curr->parent->left == curr)
                        curr->parent->left = curr->left;
                    else if(curr->parent && curr->parent->right == curr)
                        curr->parent->right = curr->left;
                    else {
                        // we can assume the number node we just created is the only node
                        // so set head to that node
                        head = curr->left;
                    }

                    curr = curr->parent;
                }
            }
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
}