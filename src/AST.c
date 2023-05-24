#include "../include/AST.h"
#include "../include/token.h"
#include <string.h>

void init_AST(struct AST *self, struct Token _token, struct AST* _children[2]) {
    memcpy(self->children, _children, 2*sizeof(struct AST*));
    self->token = _token;
}

void init_UnaryAST(struct UnaryAST *self, struct Token _token, struct AST *_expr) {
    memcpy(self->expr, _expr, sizeof(struct AST));
    self->token = _token;
}
