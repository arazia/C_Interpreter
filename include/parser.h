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

char Parser_peek(struct Parser *self);

struct ASTContainer* Parser_program(struct Parser *self);

struct ASTContainer* Parser_scope(struct Parser *self);

struct ASTContainer** Parser_statement_list(struct Parser *self, int *_ret_size);

struct ASTContainer* Parser_statement(struct Parser *self);

struct ASTContainer* Parser_assignment(struct Parser *self);

struct ASTContainer* Parser_variable(struct Parser *self);

struct ASTContainer* Parser_empty(struct Parser *self);

struct ASTContainer* Parser_factor(struct Parser *self);

struct ASTContainer* Parser_term(struct Parser *self);

struct ASTContainer* Parser_expr(struct Parser *self);

struct ASTContainer* Parser_parse(struct Parser *self);
#endif
