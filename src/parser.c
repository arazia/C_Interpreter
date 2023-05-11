#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/token.h"
#include "../include/parser.h"
#include "../include/AST.h"

void init_Parser (struct Parser *self, struct Lexer *_lexer) {
    self->lexer = _lexer;
    self->curr_token = *Lexer_get_next_token(self->lexer);
}

void Parser_eat(struct Parser *self, enum token_type t) {
    printf("type: %u  value: %s\n", self->curr_token.type, self->curr_token.value);
    if (self->curr_token.type == t) {
        self->curr_token = *Lexer_get_next_token(self->lexer);
    } else {
       printf("token cannot be eaten!\n"); 
       exit(1);
    }
}

struct AST* Parser_factor(struct Parser *self) {
    struct AST *node = malloc(sizeof(struct AST));
    if (self->curr_token.type == INTEGER) {
        struct AST *children[2] = { NULL };
        init_AST(node, self->curr_token, children);
        Parser_eat(self, INTEGER);
        return node;
     } else if (self->curr_token.type == LPARENT) {
        Parser_eat(self, LPARENT);
        node = Parser_expr(self);
        Parser_eat(self, RPARENT);
        return node;  
     } else {
        printf("factor not found! Found %d instead.\n", self->curr_token.type);
        exit(1);
    }
 }

struct AST* Parser_term(struct Parser *self) {
    struct AST *node = Parser_factor(self);

    while (self->curr_token.type == MULT || self->curr_token.type == DIV) {
        if (self->curr_token.type == MULT) {
            Parser_eat(self, MULT);
            struct AST *node_copy = malloc(sizeof(struct AST));
            memcpy(node_copy, node, sizeof(struct AST));
            struct AST *children[2] = {node_copy, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, MULT, "*");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MULT, "*");
            init_AST(node, *temp, children);
        } else if (self->curr_token.type == DIV) {
            Parser_eat(self, DIV);
            struct AST *node_copy = malloc(sizeof(struct AST));
            memcpy(node_copy, node, sizeof(struct AST));
            struct AST *children[2] = {node_copy, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, DIV, "/");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MULT, "*");
            init_AST(node, self->curr_token, children);
        } else {
            printf("term not found!\n");
            exit(1);
        }

    }

    return node;
}


struct AST* Parser_expr(struct Parser *self) {
    struct AST *node = Parser_term(self);
    while (self->curr_token.type == ADD || self->curr_token.type == MINUS) {
        if (self->curr_token.type == ADD) {
            Parser_eat(self, ADD);
            struct AST *node_copy = malloc(sizeof(struct AST));
            memcpy(node_copy, node, sizeof(struct AST));
            struct AST *children[2] = {node_copy, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, ADD, "+");
            init_AST(node, *temp, children);
        } else if (self->curr_token.type == MINUS) {
            Parser_eat(self, MINUS);
            struct AST *node_copy = malloc(sizeof(struct AST));
            memcpy(node_copy, node, sizeof(struct AST));
            struct AST *children[2] = {node_copy, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MINUS, "-");
            init_AST(node, *temp, children);
        } else {
            printf("expr not found!\n");
            exit(1);
        }
    } 

    return node; 
}

struct AST* Parser_parse(struct Parser *self) {
    return Parser_expr(self);
}


