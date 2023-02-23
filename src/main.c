#include <stdio.h>
#include "interpreter.h"
#include "lexer.h"
#include "token.h"

int main() {
    char in[301];
    in[300] = '\0';

    // struct Lexer *lexer = malloc(sizeof(struct Lexer));
    struct Interpreter interpreter;
    struct Lexer lexer;
    printf("Enter expression: ");
    fgets(lexer.text, sizeof(in) - 1, stdin);

    init_Lexer_types(&lexer);

    init_Interpreter(&interpreter, &lexer);

    int res = Interpreter_expr(&interpreter);

    printf("%d", res);

    return 0;
}
