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

int find_end(const char *s) {
    for (int i = 0; i < strlen(s)-1; i++) {
        if (s[i] == ';' && s[i+1] == ';') {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    char main_input[3000];
    char in[300];
    // struct Lexer *lexer = malloc(sizeof(struct Lexer));
    struct Parser parser;
    struct Lexer lexer;
    struct Interpreter interpreter;
    if (argc == 1) {
        printf("# ");
        while (fgets(in, sizeof(in), stdin) != NULL) {
            strcat(main_input, strip(in));
            find_end(in) ? printf("# ") : 0;
        }

        strcpy(lexer.text, main_input);

        init_Lexer_types(&lexer);

        init_Parser(&parser, &lexer);

        init_Interpreter(&interpreter, parser);

        int res = Interpreter_interpret(&interpreter);

        printf("%d", res);
    } else {
        FILE *file;
        file = fopen(argv[0], "r");
        fgets(main_input, 3000, file);



        fclose(file);
    }

    

    return 0;
}
