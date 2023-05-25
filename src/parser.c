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
        // struct BinaryAST *temp1 = (struct BinaryAST*)temp;
        // struct NumAST *temp2 = (struct NumAST*)temp1->children[0], *temp3 = (struct NumAST*)temp1->children[1];
        // printf("\n %d 0: %s 1: %s\n", temp->type, temp2->value, temp3->value);
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
        struct BinaryAST* node_temp = malloc(sizeof(struct BinaryAST));
        struct ASTContainer* node_copy = NULL;
        if (node->type == Unary) {
            node_copy = malloc(sizeof(struct UnaryAST));
            memcpy(node_copy, (struct UnaryAST*)node, sizeof(struct UnaryAST));
        } else {
            node_copy = malloc(sizeof(struct NumAST));
            memcpy(node_copy, (struct NumAST*)node, sizeof(struct NumAST));
        }
        if (self->curr_token.type == MULT) {
            Parser_eat(self, MULT);
            struct ASTContainer *children[2] = {node_copy, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, MULT, "*");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MULT, "*");
            init_BinaryAST(node_temp, *temp, children);
        } else if (self->curr_token.type == DIV) {
            Parser_eat(self, DIV);
            struct ASTContainer *children[2] = {node_copy, Parser_factor(self)};
            // struct Token *temp = malloc(sizeof(struct Token));
            // init_Token_types(temp, DIV, "/");
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, DIV, "/");
            init_BinaryAST(node_temp, *temp, children);
        } else {
            printf("term not found!\n");
            exit(1);
        }
        node = (struct ASTContainer*)node_temp;
    }
    return node;
}


struct ASTContainer* Parser_expr(struct Parser *self) {
    struct ASTContainer *node = Parser_term(self);
    struct BinaryAST *new_node = NULL;

    while (self->curr_token.type == ADD || self->curr_token.type == MINUS) {
        if (self->curr_token.type == ADD) {
            Parser_eat(self, ADD);
            new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, ADD, "+");
            init_BinaryAST(new_node, *temp, children);
        } else if (self->curr_token.type == MINUS) {
            Parser_eat(self, MINUS);
            new_node = malloc(sizeof(struct BinaryAST));
            struct ASTContainer *children[2] = {node, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MINUS, "-");
            init_BinaryAST(new_node, *temp, children);
        } else {
            printf("expr not found!\n");
            exit(1);
        }
    } 
    return (new_node != NULL) ? (struct ASTContainer*)new_node : node;
}

struct ASTContainer* Parser_parse(struct Parser *self) {
    return Parser_expr(self);
}


