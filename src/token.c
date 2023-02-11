#include <stdio.h>
#include <string.h>
#include "token.h"

void init_Token_types(struct Token *this, enum token_type _type, char _value[]) {
    this->type = _type;
    memcpy (this->value, _value, strlen(_value)+1);
}
