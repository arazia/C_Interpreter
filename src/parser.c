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
       printf("token cannot be eaten! Ate %d instead of %d\n", self->curr_token.type, t); 
       exit(1);
    }
}

struct ASTContainer* Parser_program(struct Parser *self) {
    struct ASTContainer *node = Parser_scope(self);
    Parser_eat(self, END);
    return node;
}

struct ASTContainer* Parser_scope(struct Parser *self) {
    int ret_size;
    struct ASTContainer **nodes = Parser_statement_list(self, &ret_size);

    struct ScopeAST *root = malloc(sizeof(struct ScopeAST));
    init_ScopeAST(root, nodes, ret_size);

    return (struct ASTContainer*)root;    
}

struct ASTContainer** Parser_statement_list(struct Parser *self, int *_ret_size) {
    struct ASTContainer *node = Parser_statement(self);
    struct ASTContainer **ret = malloc(500 * sizeof(struct ASTContainer*));
    ret[0] = node;
    int ret_size = 1;

    while (self->curr_token.type == SEMI) {
        Parser_eat(self, SEMI);
        ret_size++;
        ret[ret_size - 1] = Parser_statement(self);
    }

    if (self->curr_token.type == ID) {
        printf("Statement List found ID in wrong place!");
        exit(1);
    } else if (ret_size > 500) {
        printf("Current App only supports %d possible statements, you have %d!", 500, ret_size);
        exit(1);
    }
    *_ret_size = ret_size;
    return ret;
}

struct ASTContainer* Parser_statement(struct Parser *self) {
    if (self->curr_token.type == LET) {
        return Parser_assignment(self);
    } else if (self->curr_token.type == INTEGER) {
        return Parser_expr(self);
    } else if (self->curr_token.type == ID) {
        return Parser_expr(self);
    }
    else {
        return Parser_empty(self);
    }
}


struct ASTContainer* Parser_assignment(struct Parser *self) {
    Parser_eat(self, LET);
    
    struct ASTContainer *left = Parser_variable(self);
    struct Token *temp = &self->curr_token;
    Parser_eat(self, ASSIGN);
    struct ASTContainer *right = Parser_expr(self);

    struct AssignAST *ret = malloc(sizeof(struct AssignAST));

    struct ASTContainer *children[2] = {left, right};
    init_AssignAST(ret, *temp, children);

    return (struct ASTContainer*)ret;
    
}

struct ASTContainer* Parser_variable(struct Parser *self) {
    struct VariableAST *ret = malloc(sizeof(struct VariableAST));
    init_VariableAST(ret, self->curr_token);
    Parser_eat(self, ID);
    return (struct ASTContainer*)ret;
}

struct ASTContainer* Parser_empty(struct Parser *self) {
    struct EmptyAST *ret = malloc(sizeof(struct EmptyAST));
    init_EmptyAST(ret);
    return (struct ASTContainer*)ret;
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
        return Parser_variable(self);
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
        } else if (node->type == Num){
            node_copy = malloc(sizeof(struct NumAST));
            memcpy(node_copy, (struct NumAST*)node, sizeof(struct NumAST));
        } else {
            node_copy = malloc(sizeof(struct VariableAST));
            memcpy(node_copy, (struct VariableAST*)node, sizeof(struct VariableAST));
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

    while (self->curr_token.type == ADD || self->curr_token.type == MINUS) {
        struct BinaryAST* node_temp = malloc(sizeof(struct BinaryAST));
        struct ASTContainer* node_copy = NULL;
        if (node->type == Unary) {
            node_copy = malloc(sizeof(struct UnaryAST));
            memcpy(node_copy, (struct UnaryAST*)node, sizeof(struct UnaryAST));
        } else if (node->type == Num) {
            node_copy = malloc(sizeof(struct NumAST));
            memcpy(node_copy, (struct NumAST*)node, sizeof(struct NumAST));
        } else if (node->type == Binary) {
            node_copy = malloc(sizeof(struct BinaryAST));
            memcpy(node_copy, (struct BinaryAST*)node, sizeof(struct BinaryAST));
        } else {
            node_copy = malloc(sizeof(struct VariableAST));
            memcpy(node_copy, (struct VariableAST*)node, sizeof(struct VariableAST));
        }
        if (self->curr_token.type == ADD) {
            Parser_eat(self, ADD);
            struct ASTContainer *children[2] = {node_copy, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, ADD, "+");
            init_BinaryAST(node_temp, *temp, children);
        } else if (self->curr_token.type == MINUS) {
            Parser_eat(self, MINUS);
            struct ASTContainer *children[2] = {node_copy, Parser_term(self)};
            struct Token *temp = malloc(sizeof(struct Token));
            init_Token_types(temp, MINUS, "-");
            init_BinaryAST(node_temp, *temp, children);
        } else {
            printf("expr not found!\n");
            exit(1);
        }
        node = (struct ASTContainer*)node_temp;
    } 
    return node;
}

struct ASTContainer* Parser_parse(struct Parser *self) {
    return Parser_program(self);
}


