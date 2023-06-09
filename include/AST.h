#ifndef AST_H
#define AST_H

#include "token.h"

enum ASTType {
  Unary,
  Binary,
  Num,
  Scope,
  Assign,
  Variable,
  Empty
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

struct ScopeAST {
  struct ASTContainer container;
  struct ASTContainer* children[500];
  int num_children;
};

struct AssignAST {
  struct ASTContainer container;
  struct Token token;
  struct ASTContainer *children[2];
};

struct VariableAST {
  struct ASTContainer container;
  struct Token token;
  char value[20];
};

struct EmptyAST {
  struct ASTContainer container;
};

void init_UnaryAST(struct UnaryAST *self, struct Token _token, struct ASTContainer *_expr);

void init_BinaryAST(struct BinaryAST *self, struct Token _token, struct ASTContainer *_children[2]);

void init_NumAST(struct NumAST *self, struct Token _token);

void init_ScopeAST(struct ScopeAST *self, struct ASTContainer **_children, int num_children);

void init_AssignAST(struct AssignAST *self, struct Token _token, struct ASTContainer *_children[2]);

void init_VariableAST(struct VariableAST *self, struct Token _token);

void init_EmptyAST(struct EmptyAST *self);

#endif