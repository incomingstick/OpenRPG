/*
roll - roll-parser.h
Created on: Feb 12, 2017

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#ifndef SRC_ROLL_PARSER_H_
#define SRC_ROLL_PARSER_H_

#include <getopt.h>

#define FUDGE_DICE      -2 // represents a fudge die
#define HUNDRED         -1 // represents d100

/* parse tree nodes */
#define OP_NUMBER        1 // number node
#define OP_TIMES         2 // multiplication node
#define OP_DIV           3 // integer division node
#define OP_DICE          4 // n-sided dice node
#define OP_PLUS          5 // addition node
#define OP_MINUS         6 // subtraction node
#define OP_HIGH          7 // keep highest results node
#define OP_LOW           8 // keep lowest resutls node
#define OP_GT            9 // keep results greater than
#define OP_GE           10 // keep results greater or equal than
#define OP_LT           11 // keep results less than
#define OP_LE           12 // keep results less or equal than
#define OP_NE           13 // keep results different from
#define OP_REP          14 // number of rolls (repetitions)

extern bool POS_FLAG;
extern bool SUM_FLAG;

static int globalReadOffset;

// Text to read:
static const char* globalInputString = "1d6";

/* function for flex and bison to parse in a string to yyin */
int read_string(char *buff, int *numBytesRead, int maxBytesToRead);

/* node of the intermediate representation parse tree */
struct parse_node {
    struct parse_node* left;    // left node
    struct parse_node* right;   // right node
    struct parse_node* next;    // next tree
    unsigned short int op;      // node type
    int value;                  // node value
};

int checked_sum(int op1, int op2);
int checked_multiplication(int op1, int op2);

struct parse_node* allocate_node(void);
struct parse_node* new_number(int number);
struct parse_node* new_op (unsigned short int op, struct parse_node* left, struct parse_node* right);
struct parse_node* new_dice (struct parse_node* sides);

int roll_expression(struct parse_node* node, bool print);
void print_tree(std::string prefix, struct parse_node* node, int indent);

#endif  /* SRC_ROLL_PARSER_H_ */