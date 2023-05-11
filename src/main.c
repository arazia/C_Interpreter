#include <stdio.h>
#include "../include/interpreter.h"
#include "../include/lexer.h"
#include "../include/token.h"
#include "../include/parser.h"
#include "../include/AST.h"

int main() {
    char in[301];
    in[300] = '\0';

    // struct Lexer *lexer = malloc(sizeof(struct Lexer));
    struct Parser parser;
    struct Lexer lexer;
    struct Interpreter interpreter;
    printf("Enter expression: ");
    fgets(lexer.text, sizeof(in) - 1, stdin);

    init_Lexer_types(&lexer);

    init_Parser(&parser, &lexer);

    init_Interpreter(&interpreter, parser);

    int res = Interpreter_interpret(&interpreter);

    printf("%d", res);

    return 0;
}
