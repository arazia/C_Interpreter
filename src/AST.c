#include "../include/AST.h"
#include "../include/token.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_BinaryAST(struct BinaryAST *self, struct Token _token, struct ASTContainer* _children[2]) {
    self->container.type = Binary;
    memcpy(self->children, _children, 2*sizeof(struct ASTContainer*));
    // free(_children);
    self->token = _token;
}

void init_UnaryAST(struct UnaryAST *self, struct Token _token, struct ASTContainer *_expr) {
    self->container.type = Unary;
    self->expr = _expr;
    self->token = _token;
}

void init_NumAST(struct NumAST *self, struct Token _token) {
    self->container.type = Num;
    self->token = _token;
    strcpy(self->value, _token.value);
}

void init_ScopeAST(struct ScopeAST *self, struct ASTContainer **_children, int num_children) {
    self->container.type = Scope;
    self->num_children = num_children;
    memcpy(self->children, _children, num_children*sizeof(struct ASTContainer*));
    // free(_children);
}

void init_AssignAST(struct AssignAST *self, struct Token _token, struct ASTContainer* _children[2]) {
    self->container.type = Assign;
    memcpy(self->children, _children, 2*sizeof(struct ASTContainer*));
    // free(_children);
    self->token = _token;
}

void init_VariableAST(struct VariableAST *self, struct Token _token) {
    self->container.type = Variable;
    self->token = _token;
    strcpy(self->value, _token.value);
}

void init_EmptyAST(struct EmptyAST *self) {
    self->container.type = Empty;
}


