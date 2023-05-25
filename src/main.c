#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/lexer.h"
#include "../include/token.h"
#include "../include/parser.h"
#include "../include/AST.h"

char *strip(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if(p) {
        char *p2 = p;
        while(*s != '\0') {
            if(*s != '\n') {
                *p2++ = *s++;
            } else {
                ++s;
            }
        }
        *p2 = '\0';
    }
    return p;
}

int main() {
    char main_input[3000];
    char in[300];
    // struct Lexer *lexer = malloc(sizeof(struct Lexer));
    struct Parser parser;
    struct Lexer lexer;
    struct Interpreter interpreter;
    printf("# ");
    while (fgets(in, sizeof(in), stdin) != NULL) {
        strcat(main_input, strip(in));
    }

    strcpy(lexer.text, main_input);

    init_Lexer_types(&lexer);

    init_Parser(&parser, &lexer);

    init_Interpreter(&interpreter, parser);

    int res = Interpreter_interpret(&interpreter);

    printf("%d", res);

    return 0;
}
