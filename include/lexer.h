#ifndef LEXER_H
#define LEXER_H


#include "token.h"

struct Lexer {
    char text[300];
    int pos;
    char curr_char;

};

void init_Lexer_types(struct Lexer *this);

void Lexer_advance(struct Lexer *this);

char* Lexer_integer(struct Lexer *this, char *res);

void Lexer_whitespace(struct Lexer *this);

struct Token* Lexer_get_next_token(struct Lexer *this);


#endif
