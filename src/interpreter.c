#include "../include/token.h"
#include "../include/interpreter.h"
#include "../include/parser.h"
#include "../include/AST.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

void init_Interpreter(struct Interpreter *self, struct Parser _parser) {
    self->parser = _parser;
    self->global_scope_pos = 1;
}

int Interpreter_find_scope(struct Interpreter *self, char *str) {
    for (int i = 0; i < self->global_scope_pos; ++i) {
        if (strcmp(str, GLOBAL_SCOPE_VAR[i]) == 0) {
            return i;
        }
    }
    return 0;
}

void Interpreter_visit_scope(struct Interpreter *self, struct ScopeAST *node) {
    for (int i = 0; i < node->num_children; ++i) {
        Interpreter_visit(self, node->children[i]);
    }
}

void Interpreter_visit_assign(struct Interpreter *self, struct AssignAST *node) {
    char *var_name = ((struct VariableAST*)node->children[0])->value;
    int i = Interpreter_find_scope(self, var_name);   
    if (i) {
        strcpy(GLOBAL_SCOPE_VAL[i], ((struct NumAST*)node->children[1])->value);    
    } else {
        strcpy(GLOBAL_SCOPE_VAR[self->global_scope_pos], var_name);
        strcpy(GLOBAL_SCOPE_VAL[self->global_scope_pos], ((struct NumAST*)node->children[1])->value);
        self->global_scope_pos++;
    }
    
}

char* Interpreter_visit_variable(struct Interpreter *self, struct VariableAST *node) {
    char *var_name = node->value;
    char *val = GLOBAL_SCOPE_VAL[Interpreter_global_linearsearch(self, var_name)];
    if (val == 0) {
        printf("Variable name %s does not have a value!", var_name);
        exit(1);
    } else {
        return val;
    }
}

int Interpreter_global_linearsearch(struct Interpreter *self, char *search) {
    for (int i = 0; i < self->global_scope_pos; ++i) {
        if (strcmp(GLOBAL_SCOPE_VAR[i], search) == 0) {
            return i;
        }
    }
    return -1;
}

void Interpreter_visit_empty(struct Interpreter *self, struct EmptyAST *node) {
    return;
}

int Interpreter_visit_num(struct Interpreter *self, struct NumAST *node) {
    return atoi(node->value);
}

int Interpreter_visit_binop(struct Interpreter *self, struct BinaryAST *node) {
    int left_val = Interpreter_visit(self, node->children[0]);
    int right_val = Interpreter_visit(self, node->children[1]);

    if (node->token.type == ADD) {
        printf("- : int = %d\n", left_val + right_val);
        return left_val + right_val;
    } else if (node->token.type == MINUS) {
        printf("- : int = %d\n", left_val - right_val);
        return left_val - right_val;
    } else if (node->token.type == MULT) {
        printf("- : int = %d\n", left_val * right_val);
        return left_val * right_val;
    } else if (node->token.type == DIV) {
        printf("- : int = %d\n", left_val / right_val);
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
        printf("Visit UnaryOp could not find correct token type. Found %d instead.", node->token.type);
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
    } else if (node->type == Scope) {
        Interpreter_visit_scope(self, (struct ScopeAST*)node);
        return 0;
    } else if (node->type == Assign) {
        Interpreter_visit_assign(self, (struct AssignAST*)node);
        return 0;
    } else if (node->type == Variable) {
        return atoi(Interpreter_visit_variable(self, (struct VariableAST*)node));
    } else if (node->type == Empty) {
        Interpreter_visit_empty(self, (struct EmptyAST*)node);
        return 0;
    } else {
        printf("Visit did not find a correct token type. Found %d instead.", node->type);
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
    assert(tree->type == 3);
    int res = Interpreter_visit(self, tree);
    return res;
}