/*
roll-parser-test.cpp - Test program for roll-parser
Created on: Dec 1, 2016

OpenRPG Software License - Version 1.0 - February 10th, 2017 <http://www.openrpg.io/about/license/>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/
#include <iostream>

#include "roll/roll-parser.h"

using namespace std;

int main(int argc, char* argv[]) {
    // TODO roll parser test cases 
    ExpressionTree tree_d4;
    ExpressionTree tree_d6;
    ExpressionTree tree_d8;
    ExpressionTree tree_d10;
    ExpressionTree tree_d12;
    ExpressionTree tree_d20;
    ExpressionTree tree_d100;

    /* Once we have a test suite api built/chosen make these expressions far more complex to ensure the enrigirty of our  */
    tree_d4.set_expression("1d4");
    tree_d6.set_expression("1d6");
    tree_d8.set_expression("1d8");
    tree_d10.set_expression("1d10");
    tree_d12.set_expression("1d12");
    tree_d20.set_expression("1d20");
    tree_d100.set_expression("1d100");
    
    int d4      = tree_d4.parse_expression();
    int d6      = tree_d6.parse_expression();
    int d8      = tree_d8.parse_expression();
    int d10     = tree_d10.parse_expression();
    int d12     = tree_d12.parse_expression();
    int d20     = tree_d20.parse_expression();
    int d100    = tree_d100.parse_expression();
    
    if(d4 > 4 || d4 < 0)        return 1;
    if(d6 > 8 || d6 < 0)        return 1;
    if(d8 > 8 || d8 < 0)        return 1;
    if(d10 > 10 || d10 < 0)     return 1;
    if(d12 > 12 || d12 < 0)     return 1;
    if(d20 > 20 || d20 < 0)     return 1;
    if(d100 > 100 || d100 < 0)  return 1;
    
    return 0;
}
