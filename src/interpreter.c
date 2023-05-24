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

int Interpreter_visit_num(struct Interpreter *self, struct AST *node) {
    if (node->token.type == INTEGER) {
        return atoi(node->token.value);
    }
    printf("visit_num did not find an integer! Found %d instead.", node->token.type);
    exit(1);
}

int Interpreter_visit_binop(struct Interpreter *self, struct AST *node) {
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

int Interpreter_visit(struct Interpreter *self, struct AST *node) {
    if (node->token.type == INTEGER) {
        return Interpreter_visit_num(self, node);
    } else if (node->token.type == ADD || node->token.type == MINUS || node->token.type == MULT || node->token.type == DIV) {
        return Interpreter_visit_binop(self, node);
    } else {
        printf("Visit did not find a correct token type.");
        exit(1);
    }
}

void inorder(struct AST *head) {
    if (head == NULL) {
        return;
    }
    
    inorder(head->children[0]);
    printf("%d %s\n", head->token.type, head->token.value);
    inorder(head->children[1]);
}


int Interpreter_interpret(struct Interpreter *self) {
    struct AST *tree = Parser_parse(&self->parser);
    inorder(tree);
    int res = Interpreter_visit(self, tree);
    return res;
}