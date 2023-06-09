#ifndef INTERPRETER_H
#define INTERPRETER_H


#include "parser.h"

static char GLOBAL_SCOPE_VAR[100][100];

static char GLOBAL_SCOPE_VAL[100][100];

struct Interpreter {
  struct Parser parser;
  int global_scope_pos;
};

void init_Interpreter(struct Interpreter *self, struct Parser _parser);

void Interpreter_visit_scope(struct Interpreter *self, struct ScopeAST *node);

void Interpreter_visit_assign(struct Interpreter *self, struct AssignAST *node);

char* Interpreter_visit_variable(struct Interpreter *self, struct VariableAST *node);

int Interpreter_global_linearsearch(struct Interpreter *self, char *search);

void Interpreter_visit_empty(struct Interpreter *self, struct EmptyAST *node);

int Interpreter_visit_num(struct Interpreter *self, struct NumAST *node);

int Interpreter_visit_binop(struct Interpreter *self, struct BinaryAST *node);

int Interpreter_visit_unaryop(struct Interpreter *self, struct UnaryAST *node);

int Interpreter_visit(struct Interpreter *self, struct ASTContainer *node);

int Interpreter_interpret(struct Interpreter *self);

#endif