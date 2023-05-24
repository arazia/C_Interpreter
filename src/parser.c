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

struct ASTContainer* Parser_factor(struct Parser *self) {
    if (self->curr_token.type == ADD) {
        struct UnaryAST *unary_node = malloc(sizeof(struct UnaryAST));
        // struct AST *children[2] = { NULL };
        Parser_eat(self, ADD);
        struct Token *temp = malloc(sizeof(struct Token));
        init_Token_types(temp, ADD, "+");
        init_UnaryAST(unary_node, *temp, Parser_factor(self));
        return (struct ASTContainer*)unary_node;
    } else if (self->curr_token.type == MINUS) {
        struct UnaryAST *unary_node = malloc(sizeof(struct UnaryAST));
        Parser_eat(self, MINUS);
        struct Token *temp = malloc(sizeof(struct Token));
        init_Token_types(temp, MINUS, "-");
        init_UnaryAST(unary_node, *temp, Parser_factor(self));
        return (struct ASTContainer*)unary_node;
    } else if (self->curr_token.type == INTEGER) {
        struct NumAST *num_node = malloc(sizeof(struct NumAST));
        init_NumAST(num_node, self->curr_token);
        Parser_eat(self, INTEGER);
        return (struct ASTContainer*)num_node;
     } else if (self->curr_token.type == LPARENT) {
        struct ASTContainer *temp = malloc(sizeof(struct ASTContainer));
        Parser_eat(self, LPARENT);
        temp = Parser_expr(self);
        Parser_eat(self, RPARENT);
        return temp;  
     } else {
        printf("factor not found! Found %d instead.\n", self->curr_token.type);
        exit(1);
    }
 }

struct ASTContainer* Parser_term(struct Parser *self) {
    struct ASTContainer *node = Parser_factor(self);

    while (self->curr_token.type == MULT || self->curr_token.type == DIV) {
        if (self->curr_token.type == MULT) {
            Parser_eat(self, MULT);
            struct BinaryAST *new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, MULT, "*");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MULT, "*");
            init_BinaryAST(new_node, *temp, children);
            return (struct ASTContainer*)new_node;
        } else if (self->curr_token.type == DIV) {
            Parser_eat(self, DIV);
            struct BinaryAST *new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, DIV, "/");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, DIV, "/");
            init_BinaryAST(new_node, *temp, children);
            return (struct ASTContainer*)new_node;
        } else {
            printf("term not found!\n");
            exit(1);
        }
    }
    return node;
}


struct ASTContainer* Parser_expr(struct Parser *self) {
    struct ASTContainer *node = Parser_term(self);
    while (self->curr_token.type == ADD || self->curr_token.type == MINUS) {
        if (self->curr_token.type == ADD) {
            Parser_eat(self, ADD);
            struct BinaryAST *new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, ADD, "+");
            init_BinaryAST(new_node, *temp, children);
            return (struct ASTContainer*)new_node;
        } else if (self->curr_token.type == MINUS) {
            Parser_eat(self, MINUS);
            struct BinaryAST *new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MINUS, "-");
            init_BinaryAST(new_node, *temp, children);
            return (struct ASTContainer*)new_node;
        } else {
            printf("expr not found!\n");
            exit(1);
        }
    } 
    return node;
}

struct ASTContainer* Parser_parse(struct Parser *self) {
    return Parser_expr(self);
}


