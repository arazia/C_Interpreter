#ifndef AST_H
#define AST_H



#include "token.h"

struct AST {
  struct Token token;
  struct AST* children[2];
};

struct UnaryAST {
  struct AST *expr;
  struct Token token;
};

void init_UnaryAST(struct UnaryAST *self, struct Token _token, struct AST *_expr);

void init_AST(struct AST *self, struct Token _token, struct AST *_children[2]);


#endif