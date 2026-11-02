%{
#include "config.tab.h"
#include <string.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]* { 
    yylval.str = strdup(yytext); 
    return IDENTIFIER; 
}

[0-9]+ { 
    yylval.num = atoi(yytext); 
    return NUMBER; 
}

[-+*/=;\n] { 
    return yytext[0]; 
}

[ \t] { }

. { }

%%

int yywrap() { 
    return 1; 
}