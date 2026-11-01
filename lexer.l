%{
#include <stdio.h>
%}

/* Regular expression definitions */
DIGIT    [0-9]
ID       [a-zA-Z_][a-zA-Z0-9_]*

%%

"int"|"float"|"if"|"else"|"return" { printf("KEYWORD: %s\n", yytext); }

{ID}        { printf("IDENTIFIER: %s\n", yytext); }

{DIGIT}+    { printf("NUMBER (INTEGER): %s\n", yytext); }

"+"|"-"|"*"|"/" { printf("ARITHMETIC OPERATOR: %s\n", yytext); }
"="         { printf("ASSIGNMENT OPERATOR: %s\n", yytext); }
"=="|"!="   { printf("RELATIONAL OPERATOR: %s\n", yytext); }
";"|","     { printf("PUNCTUATOR: %s\n", yytext); }

[ \t\n]+    { /* Ignore whitespace and newlines */ }

.           { printf("UNKNOWN TOKEN: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter code (Press Ctrl+D to stop):\n");
    yylex();
    return 0;
}


/*
sudo apt update
sudo apt install flex gcc -y

flex lexer.l

gcc lex.yy.c -o lexer

./lexer


Once it is running, type some test code (like int main() { }) and press Enter. The program will output the identified tokens.

To stop the program and return to the normal terminal prompt, press Ctrl+D on an empty line.

*/