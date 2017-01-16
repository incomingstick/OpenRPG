%{
/*
roll - parser.c
Created on: Jan 16, 2017

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include <stdio.h>
#include "die.h"
#include "util.h"

bool POS_FLAG = false;
  
int  yylex(void);
void yyerror(char const*);
  
%}

%union {
    struct ir_node* node;
    int int_type;
}

%token COMMA
%token DICE
%token DIV
%token FUDGE
%token HIGH
%token LCURLY
%token LOW
%token LPAREN
%token MINUS
%token PERCENT
%token PLUS
%token RCURLY
%token RPAREN
%token TIMES
%token LE
%token LT
%token GE
%token GT
%token NE
%token <int_type> NUMBER

%type <node> dice
%type <node> filtered_dice
%type <node> term
%type <node> factor
%type <node> expression
%type <node> expression_list
%type <int_type> top_level_expression
%type <int_type> top_level_expression_list

%start roll

%%

roll : top_level_expression_list {      
    printf("sum: %i\n", $1);
}
;

top_level_expression_list : top_level_expression {
    if (!POS_FLAG || $1 > 0) {
        $$ = $1;
    } else {
        $$ = 0;
    }
}
| top_level_expression COMMA top_level_expression_list {
    $$ = $1 + $3;
}
;

top_level_expression : expression {
#ifdef DEBUG
    if (debug_flag > 0) {
        print_tree("tree", $1, 0);
    }
#endif
    $$ = roll_expression($1, TRUE);
}
| LCURLY expression_list RCURLY {
#ifdef DEBUG
    if (debug_flag > 0) {
        print_tree("tree", $2, 0);
    }
#endif
    $$ = roll_expression($2, TRUE);
}
| NUMBER LCURLY expression_list RCURLY {
    int repetitions = $1;
    int i;
    int res;
    int sum = 0;

#ifdef DEBUG
    if (debug_flag > 0) {
        print_tree("tree", $3, 0);
    }
#endif
  for (i = 0; i < repetitions; i++) {
    res = roll_expression($3, TRUE);
    if (sum_flag == TRUE) {
      printf("sum: %i\n", res);
      sum += res;
    }

  }

  $$ = sum;
  
}
;

expression_list : expression {
  $$ = $1;
}
| expression COMMA expression_list {
  $1->next = $3;
  $$ = $1;
}
;

expression : term {
  $$ = $1;
}
| expression PLUS term {
  $$ = new_op(OP_PLUS, $1, $3);
}
| expression MINUS term {
  $$ = new_op(OP_MINUS, $1, $3);
}
;

factor   :   NUMBER filtered_dice {

  $$ = new_op(OP_REP, new_number($1), $2);
  
}
| NUMBER filtered_dice HIGH NUMBER {

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $$ = new_op(OP_HIGH, new_number($4), new_op(OP_REP, new_number($1), $2));

}
| NUMBER filtered_dice LOW NUMBER {

  if ($4 > $1) {
    error("the number of kept dices must be lower than the actual dices");
  }

  $$ = new_op(OP_LOW, new_number($4), new_op(OP_REP, new_number($1), $2));

}
| filtered_dice {
  $$ = $1;
}
;


term     :   NUMBER {
  $$ = new_number($1);
}
| factor {
  $$ = $1;
}
| factor TIMES NUMBER {
  $$ = new_op(OP_TIMES, $1, new_number($3));
}
| factor DIV NUMBER {
  $$ = new_op(OP_DIV, $1, new_number($3));
}
| NUMBER TIMES factor {
  $$ = new_op(OP_TIMES, new_number($1), $3);
}
| NUMBER DIV factor {
  $$ = new_op(OP_DIV, new_number($1), $3);
}
| LPAREN expression RPAREN {
  $$ = $2;
}
;

filtered_dice : dice {
  $$ = $1;
}
| dice GT NUMBER {
  $$ = new_op(OP_GT, $1, new_number($3));
  
}
| dice GE NUMBER {
  $$ = new_op(OP_GE, $1, new_number($3));
}
| dice LT NUMBER {
  $$ = new_op(OP_LT, $1, new_number($3));
}
| dice LE NUMBER {
  $$ = new_op(OP_LE, $1, new_number($3));
}
| dice NE NUMBER {
  $$ = new_op(OP_NE, $1, new_number($3));
}
;

dice       : DICE NUMBER {
  $$ = new_dice(new_number($2));
}
| DICE {
  $$ = new_dice(new_number(6));
}
| DICE PERCENT {
  $$ = new_dice(new_number(HUNDRED));
}
| DICE FUDGE {
  $$ = new_dice(new_number(FUDGE_DICE));
}
;

%%

void yyerror (char const * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}


