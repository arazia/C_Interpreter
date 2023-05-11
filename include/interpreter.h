#ifndef INTERPRETER_H
#define INTERPRETER_H


#include "parser.h"

struct Interpreter {
  struct Parser parser;
};

void init_Interpreter(struct Interpreter *self, struct Parser _parser);

int Interpreter_visit_num(struct Interpreter *self, struct AST *node);

int Interpreter_visit_binop(struct Interpreter *self, struct AST *node);

int Interpreter_visit(struct Interpreter *self, struct AST *node);

int Interpreter_interpret(struct Interpreter *self);

#endif