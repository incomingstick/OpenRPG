%option noyywrap

%{
/*
roll - scanner.c
Created on: Jan 16, 2017

License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
*/

#include <climits>
#include "roll-parser.hpp"

extern int read_string(char* buff, int *numBytesRead, int maxBytesToRead);

#undef YY_INPUT
#define YY_INPUT(b,r,s) read_string(b, &r, s)

int yylex(void);

%} 

%%

[0-9]+      {
    errno = 0;
    long number =  strtol(yytext, NULL, 10);

    /* sanity check correct number */
    if(errno != 0 && errno != ERANGE && number == 0) {
        printf("Error: incorrect number %s\n", yytext);
        exit(EXIT_FAILURE);
    }

    /* we only accept integers */
    if(number > INT_MAX) {
        printf("Error: %s is too large\n", yytext );
        exit(EXIT_FAILURE);
    }

    yylval.int_type = (int)number;

    return NUMBER;
}
\+          { return PLUS;    }
\-          { return MINUS;   }
['*'|x]      { return TIMES;   }
\/          { return DIV;     }
d|D         { return DICE;    }
f|F         { return FUDGE;   }
h|H         { return HIGH;    }
l|L         { return LOW;     }
"("         { return LPAREN;  }
")"         { return RPAREN;  }
"{"         { return LCURLY;  }
"}"         { return RCURLY;  }
">"         { return GT; }
">="        { return GE; }
"<"         { return LT; }
"<="        { return LE; }
"!="        { return NE; }
"<>"        { return NE; }
"%"         { return PERCENT; }
,           { return COMMA;   }
[[:blank:]] /* ignore spaces */
.           { 
    printf("Error: unknown symbol '%s'\n", yytext);
    exit(EXIT_FAILURE);
}

%%
