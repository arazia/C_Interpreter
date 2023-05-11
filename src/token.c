#include <stdio.h>
#include <string.h>
#include "../include/token.h"

void init_Token_types(struct Token *self, enum token_type _type, char _value[]) {
    self->type = _type;
    memcpy (self->value, _value, strlen(_value)+1);
}
