#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"
#include "interpreter.h"


void init_Interpreter (struct Interpreter *this, struct Lexer *_lexer) {
    this->lexer = *_lexer;
    this->curr_token = *Lexer_get_next_token(&this->lexer);
}

void Interpreter_eat(struct Interpreter *this, enum token_type t) {
    printf("type: %u  value: %s\n", this->curr_token.type, this->curr_token.value);
    if (this->curr_token.type == t) {
        this->curr_token = *Lexer_get_next_token(&this->lexer);
    } else {
       printf("token cannot be eaten!\n"); 
       exit(0);
    }
}

int Interpreter_factor(struct Interpreter *this) {
    int ret = atoi(this->curr_token.value);
    Interpreter_eat(this, INTEGER);
    return ret;
}

int Interpreter_term(struct Interpreter *this) {
    int res = Interpreter_factor(this);

    while (this->curr_token.type == 3 || this->curr_token.type == 4) {
        if (this->curr_token.type == 3) {
            Interpreter_eat(this, MULT);
            res *= Interpreter_factor(this);
        } else if (this->curr_token.type == 4) {
            Interpreter_eat(this, DIV);
            res /= Interpreter_factor(this);
        } else {
            printf("term not found!\n");
            exit(0);
        }

    }

    return res;
}


int Interpreter_expr(struct Interpreter *this) {
    int result = Interpreter_term(this);
    while (this->curr_token.type == 1 || this->curr_token.type == 2) {
        if (this->curr_token.type == 1) {
            Interpreter_eat(this, ADD);
            result += Interpreter_term(this);
        } else if (this->curr_token.type == 2) {
            Interpreter_eat(this, MINUS);
            result -= Interpreter_term(this);
        } else {
            printf("expr not founf!\n");
            exit(0);
        }
    } 

    return result; 
}
