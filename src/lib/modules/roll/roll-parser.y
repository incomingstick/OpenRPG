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

void print_node(struct ir_node* node) {
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

void print_tree(char* prefix, struct ir_node* node, int indent) {
    int i;
  
    printf("[%s] ", prefix);

    for(i = 0; i < indent; i++) {
        printf("  ");
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

int roll_expression(struct ir_node* node, bool print) {
    int high;
    int i;
    int limit;
    int low;
    int repetitions;
    int return_value = 0;
    int sides;
    int tmp;
    int* results;

    struct ir_node* cur;

    cur = node;
    while (cur != NULL) {
        int sum = 0;

        switch(cur->op) {
        case OP_NUMBER:
            sum = cur->value;
            break;

        case OP_REP:
            for (i = 0; i < roll_expression(cur->left, false); i++)
                sum = checked_sum(sum, roll_expression(cur->right, false));
            break;
      
        case OP_DICE:
            sum = roll_dice( roll_expression(cur->right, false) );
            break;
      
        case OP_PLUS:
            sum = checked_sum(roll_expression(cur->left, false),
                              roll_expression(cur->right, false));
            break;
      
        case OP_MINUS:
            sum = checked_sum(roll_expression(cur->left, falase),
                             -roll_expression(cur->right, false));
            break;
      
        case OP_TIMES:
            sum = checked_multiplication(roll_expression(cur->left, false),
                                         roll_expression( cur->right, false));
            break;
      
        case OP_DIV:
            sum = (int)
            ceil((float)roll_expression(cur->left, FALSE) /
                        roll_expression(cur->right, FALSE));
            break;
      
        case OP_HIGH:
            sides       = roll_expression(cur->right->right->right, FALSE);
            repetitions = roll_expression(cur->right->left,  FALSE);
            high        = roll_expression(cur->left, FALSE);      

            /* array to store the results to sort */
            if (!(results = malloc(sizeof(int)*repetitions))) {
                error("Out of memory");
            }
      
            for(i=0; i<repetitions; i++) {
                results[i] = roll_dice(sides);
            }

            qsort(results, repetitions, sizeof(int), &compare);

            for(i=(repetitions-high); i<repetitions; i++) {
                sum = checked_sum( sum, results[i] );
            }
      
            free(results);
            break;
      
        case OP_LOW:
            sides       = roll_expression(cur->right->right->right, FALSE);
            repetitions = roll_expression(cur->right->left,  FALSE);
            low         = roll_expression(cur->left, FALSE);
      
            if (cur->right->left != NULL) {
                repetitions = roll_expression(cur->right->left, FALSE);
            }
                  
            /* array to store the results to sort */
            if (!(results = malloc(sizeof(int)*repetitions))) {
                error("Out of memory");
            }
      
            for(i=0; i<repetitions; i++) {
                results[i] = roll_dice(sides);
            }

            qsort(results, repetitions, sizeof(int), &compare);
      
            for(i=0; i<low; i++) {
                sum = checked_sum( sum, results[i] );
            }
      
            free(results);
            break;

        case OP_GT:
            limit = roll_expression(cur->right, FALSE);      
            tmp   = roll_expression(cur->left,  FALSE);
            
            while (tmp <= limit) {
                tmp = roll_expression(cur->left, FALSE);
            }
            
            sum = checked_sum( sum, tmp );
            break;
      
        case OP_GE:
            limit = roll_expression(cur->right, FALSE);      
            tmp   = roll_expression(cur->left,  FALSE);
            
            while (tmp < limit) {
                tmp = roll_expression(cur->left, FALSE);
            }
      
            sum = checked_sum( sum, tmp );
            break;
      
        case OP_LT:
            limit = roll_expression(cur->right, FALSE);      
            tmp   = roll_expression(cur->left,  FALSE);
      
            while (tmp >= limit) {
                tmp = roll_expression(cur->left, FALSE);
            }
      
            sum = checked_sum( sum, tmp );
      
            break;
      
        case OP_LE:
            limit = roll_expression(cur->right, FALSE);      
            tmp   = roll_expression(cur->left,  FALSE);
      
            while (tmp > limit) {
                tmp = roll_expression(cur->left, FALSE);
            }
      
            sum = checked_sum( sum, tmp );
            break;
        
        case OP_NE:
            limit = roll_expression(cur->right, FALSE);      
            tmp   = roll_expression(cur->left,  FALSE);
      
            while (tmp == limit) {
                tmp = roll_expression(cur->left, FALSE);
            }
      
            sum = checked_sum( sum, tmp );
            break;
    
        default:
            fprintf(stderr, "Implementation error: unkown IR node with code %i\n", cur->op);
            exit(EXIT_FAILURE);      
        }

        return_value = checked_sum( return_value, sum);
    
        if (print == TRUE) {
            printf("%i\n", sum);
        }
    
        cur = cur->next;
    }

    return return_value;
}
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
    if(VB_FLAG)
        print_tree("tree", $1, 0);

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


