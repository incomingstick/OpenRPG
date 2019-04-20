---
layout: docs
title: ExpressionTree
description: Scan and parse a string to preform advance die math
group: documentation
---

**Namespace:** ORPG 
**Assembly:** _none_  

## Definition
Defined in `#include "roll-parser.h"`
````
class ExpressionTree {
    public:
        void set_expression(const std::string exp);
        void scan_expression();
        int parse_expression();
        int checked_sum(int op1, int op2);
        int checked_multiplication(int op1, int op2);
        std::string to_string();
};
````

## Member functions

Function      | Description |
 ------------ | ----------- |
void set_expression(const std::string exp)  | sets the expression to be scanned and parsed equal to `exp` |
void scan_expression()    | scans the expression, creating a tree of `parse_nodes*` to be parsed |
int parse_expression()    | parses the ExpressionTree of parse nodes returning the result of the expression as an integer value |
int checked_sum(int op1, int op2)    | ensures the additon of op1 and op2 will not overflow |
int checked_multiplication(int op1, int op2)    | ensures the multiplaction of op1 by op2 will not overflow |
std::string to_string()    | returns a string representation of the current ExpressionTree |