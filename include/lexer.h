#ifndef LEXER_H
#define LEXER_H


#include "token.h"

#define RESERVED_KEYWORD_LENGTH 2

static char RESERVED_KEYWORDS[RESERVED_KEYWORD_LENGTH][100] = {
    "let",
    "in"
};

struct Lexer {
    char text[300];
    int pos;
    char curr_char;

};

void init_Lexer_types(struct Lexer *self);

void Lexer_advance(struct Lexer *self);

char* Lexer_integer(struct Lexer *self, char *res);

void Lexer_whitespace(struct Lexer *self);

struct Token* Lexer_reserved_handler(char *str);

struct Token* Lexer_reserved_task(int index, struct Token *ret);

struct Token* Lexer_id(struct Lexer *self);

char Lexer_peek(struct Lexer *self);

struct Token* Lexer_get_next_token(struct Lexer *self);


#endif
