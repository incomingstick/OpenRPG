/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_ROLL_PARSER_H_
#define SRC_ROLL_PARSER_H_

#include "roll/die.h"

#define FUDGE_DIE       -2 // represents a fudge die
#define HUNDRED         -1 // represents d100

/* parse tree nodes */
#define OP_NUMBER        1 // number node
#define OP_TIMES         2 // multiplication node
#define OP_DIV           3 // integer division node
#define OP_DIE           4 // n-sided die node
#define OP_PLUS          5 // addition node
#define OP_MINUS         6 // subtraction node
#define OP_HIGH          7 // keep highest results node
#define OP_LOW           8 // keep lowest resutls node
#define OP_GT            9 // keep results greater than
#define OP_GE           10 // keep results greater or equal than
#define OP_LT           11 // keep results less than
#define OP_LE           12 // keep results less or equal than
#define OP_NE           13 // keep results not equal to
#define OP_REP          14 // number of rolls (repetitions)

/* node of the intermediate representation parse tree */
struct parse_node {
    struct parse_node* left;    // left node
    struct parse_node* right;   // right node
    struct parse_node* parent;  // this nodes parent
    unsigned short int op;      // node type
    int value;                  // node value
};

class ExpressionTree {
private:
    parse_node* allocate_node();
    parse_node* new_number(struct parse_node* cur, int* numBytesToRead = 0);
    parse_node* new_op(struct parse_node* cur, unsigned short int op);
    parse_node* new_die(struct parse_node* cur);
    
    int parse_input_string(std::string* buff, int* numBytesRead, int maxBytesToRead);
    int parse_tree(struct parse_node* node);
    bool build_expression_tree();
    
    std::string tree_string(struct parse_node* node, int indent, std::string pre = "head->");
    
    int globalReadOffset = 0;
    struct parse_node* head = allocate_node();
    std::string inputString = "1d20";
public:
    /**
     * @desc sets the input string to be scanned and parsed equal to the string exp
     * @param const std::string exp - the string to become the input string
     */
    bool set_expression(const std::string exp);
    
    /**
     * @desc parses the parse_node tree and returns the end result of the expression
     * @return int - the end result of the expression
     */
    int parse_expression() { return parse_tree(head); };
    
    int checked_sum(int op1, int op2);
    int checked_multiplication(int op1, int op2);
    
    /**
     * @desc returns a string of the tree starting with
     *     the top node node and taking precidence over the left node
     * @return string - a string representation of the current tree
     */
    std::string to_string() { return tree_string(head, 0); };

    static bool is_exppression_valid(const std::string exp);
};

#endif  /* SRC_ROLL_PARSER_H_ */
