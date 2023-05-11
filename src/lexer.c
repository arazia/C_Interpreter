#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/token.h"
#include "../include/lexer.h"


void init_Lexer_types(struct Lexer *self) { // constructor for Lexer
    // memcpy (self->text, i, strlen(i));
    self->pos = 0;
    self->curr_char = self->text[0];
}

void Lexer_advance(struct Lexer *self) {  // helper function for next_token
    self->pos += 1;
    self->curr_char = self->text[self->pos];
}

char* Lexer_integer(struct Lexer *self, char *res) {
    int index = 0;
    while (self->curr_char != '\0' && isdigit(self->curr_char)) {
        // printf("ci: %c\n", self->curr_char);
        res[index] = self->curr_char;
        Lexer_advance(self);
        index++;
    }

    res[index] = '\0';
    return res;
}

void Lexer_whitespace(struct Lexer *self) {
    while (self->curr_char != '\0' && isspace(self->curr_char)) {
        Lexer_advance(self);
    }
}

struct Token* Lexer_get_next_token(struct Lexer *self) {
    while (self->curr_char != '\0') {

        if (isspace(self->curr_char)) {
            Lexer_whitespace(self);
            continue;
        }


        if (isdigit(self->curr_char)) {
                struct Token *ret = malloc(sizeof(struct Token));
                // Lexer_integer(self, &(ret->value));
                init_Token_types(ret, INTEGER, Lexer_integer(self, ret->value));
                // Lexer_advance(self);
                return ret;
        }

        if (self->curr_char == '+') {
                struct Token *ret = malloc(sizeof(struct Token));
                init_Token_types(ret, ADD, "+");
                Lexer_advance(self);
                return ret;
        }

        if (self->curr_char == '-') {
                struct Token *ret = malloc(sizeof(struct Token));
                init_Token_types(ret, MINUS, "-");
                Lexer_advance(self);
                return ret;
        }

        if (self->curr_char == '*') {
            struct Token *ret = malloc(sizeof(struct Token));
            init_Token_types(ret, MULT, "*");
            Lexer_advance(self);
            return ret;
        }

        if (self->curr_char == '/') {
            struct Token *ret = malloc(sizeof(struct Token));
            init_Token_types(ret, DIV, "/");
            Lexer_advance(self);
            return ret;
        }
        if (self->curr_char == '(') {
            struct Token *ret = malloc(sizeof(struct Token));
            init_Token_types(ret, LPARENT, "(");
            Lexer_advance(self);
            return ret;
        }
        
    if (self->curr_char == ')') {
            struct Token *ret = malloc(sizeof(struct Token));
            init_Token_types(ret, RPARENT, ")");
            Lexer_advance(self);
            return ret;
        }
    }

    struct Token *ret = malloc(sizeof(struct Token));
    init_Token_types(ret, END, "E");
    return ret;

}
