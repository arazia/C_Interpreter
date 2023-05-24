#ifndef AST_H
#define AST_H

#include "token.h"

enum ASTType {
  Unary,
  Binary,
  Num
};


struct ASTContainer {
  enum ASTType type;
};


struct BinaryAST {
  struct ASTContainer container;
  struct Token token;
  struct ASTContainer* children[2];
};

struct UnaryAST {
  struct ASTContainer container;
  struct ASTContainer *expr;
  struct Token token;
};

struct NumAST {
  struct ASTContainer container;
  struct Token token;
  char value[20];
};


void init_UnaryAST(struct UnaryAST *self, struct Token _token, struct ASTContainer *_expr);

void init_BinaryAST(struct BinaryAST *self, struct Token _token, struct ASTContainer *_children[2]);

void init_NumAST(struct NumAST *self, struct Token _token);

#endif