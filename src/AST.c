#include "../include/AST.h"
#include "../include/token.h"
#include <string.h>

void init_AST(struct AST *self, struct Token _token, struct AST* _children[2]) {
    memcpy(self->children, _children, 2*sizeof(struct AST*));
    self->token = _token;
}


