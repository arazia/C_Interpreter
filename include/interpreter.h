#ifndef INTERPRETER_H
#define INTERPRETER_H


#include "lexer.h"
#include "token.h"

struct Interpreter {
    struct Lexer lexer;
    struct Token curr_token;
};

void init_Interpreter(struct Interpreter *this, struct Lexer *_lexer);

void Interpreter_eat(struct Interpreter *this, enum token_type t);

int Interpreter_factor(struct Interpreter *this);

int Interpreter_term(struct Interpreter *this);

int Interpreter_expr(struct Interpreter *this);

#endif
