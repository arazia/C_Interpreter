#ifndef PARSER_H
#define PARSER_H


#include "lexer.h"
#include "token.h"
#include "AST.h"
struct Parser {
    struct Lexer *lexer;
    struct Token curr_token;
};

void init_Parser(struct Parser *self, struct Lexer *_lexer);

void Parser_eat(struct Parser *self, enum token_type t);

struct AST* Parser_factor(struct Parser *self);

struct AST* Parser_term(struct Parser *self);

struct AST* Parser_expr(struct Parser *self);

struct AST* Parser_parse(struct Parser *self);
#endif