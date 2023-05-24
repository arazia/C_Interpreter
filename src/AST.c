#include "../include/AST.h"
#include "../include/token.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_BinaryAST(struct BinaryAST *self, struct Token _token, struct ASTContainer* _children[2]) {
    self->container.type = Binary;
    memcpy(self->children, _children, 2*sizeof(struct ASTContainer*));
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