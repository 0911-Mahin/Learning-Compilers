#include "token.h"
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
extern int yylex();
extern char *yytext;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide a file to scan");
        exit(EXIT_FAILURE);
    }
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("could not open program.c!\n");
        return 1;
    }
    while (1) {
        token_t t = yylex();
        if (t == TOKEN_EOF)
            break;
        printf("token: %d text: %s\n", t, yytext);
    }
}
