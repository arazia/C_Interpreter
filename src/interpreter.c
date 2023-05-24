#include "../include/token.h"
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/AST.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

void init_Interpreter(struct Interpreter *self, struct Parser _parser) {
    self->parser = _parser;
}

int Interpreter_visit_num(struct Interpreter *self, struct NumAST *node) {
    return atoi(node->value);
}

int Interpreter_visit_binop(struct Interpreter *self, struct BinaryAST *node) {
    int left_val = Interpreter_visit(self, node->children[0]);
    int right_val = Interpreter_visit(self, node->children[1]);

    if (node->token.type == ADD) {
        return left_val + right_val;
    } else if (node->token.type == MINUS) {
        return left_val - right_val;
    } else if (node->token.type == MULT) {
        return left_val * right_val;
    } else if (node->token.type == DIV) {
        return left_val / right_val;
    } else {
        printf("visit binop could not find correct token type.");
        exit(1);
    }
}

int Interpreter_visit_unaryop(struct Interpreter *self, struct UnaryAST *node) {
    if (node->token.type == ADD) {
        return +Interpreter_visit(self, node->expr);
    } else if (node->token.type == MINUS) {
        return -Interpreter_visit(self, node->expr);
    } else {
        printf("Visit UnaryOp could not find correct token type.");
        exit(1);
    }
}

int Interpreter_visit(struct Interpreter *self, struct ASTContainer *node) {
    if (node->type == Num) {
        return Interpreter_visit_num(self, (struct NumAST*)node);
    } else if (node->type == Binary) {
        return Interpreter_visit_binop(self, (struct BinaryAST*)node);
    } else if (node->type == Unary) {
        return Interpreter_visit_unaryop(self, (struct UnaryAST*)node);
    } else {
        printf("Visit did not find a correct token type.");
        exit(1);
    }
}

void inorder(struct ASTContainer *head) {
    if (head == NULL) {
        return;
    }
}

void unarytraversal(struct ASTContainer *head) {
    struct UnaryAST *temp = (struct UnaryAST*)head;
    printf("1: %s\n", temp->token.value);    
    struct NumAST *temp2 = (struct NumAST*)temp->expr;
    printf("1: %s\n", temp2->token.value);    
        
}


int Interpreter_interpret(struct Interpreter *self) {
    struct ASTContainer *tree = Parser_parse(&self->parser);
    int res = Interpreter_visit(self, tree);
    return res;
}