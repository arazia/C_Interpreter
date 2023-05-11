#ifndef AST_H
#define AST_H



#include "token.h"

struct AST {
  struct Token token;
  struct AST* children[2];
};


void init_AST(struct AST *self, struct Token _token, struct AST *_children[2]);


#endif