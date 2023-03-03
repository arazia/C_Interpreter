#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../include/token.h"
#include "../include/lexer.h"


void init_Lexer_types(struct Lexer *this) { // constructor for Lexer
    // memcpy (this->text, i, strlen(i));
    this->pos = 0;
    this->curr_char = this->text[0];
}

void Lexer_advance(struct Lexer *this) {  // helper function for next_token
    this->pos += 1;
    this->curr_char = this->text[this->pos];
}

char* Lexer_integer(struct Lexer *this, char *res) {
    int index = 0;
    while (this->curr_char != '\0' && isdigit(this->curr_char)) {
        // printf("ci: %c\n", this->curr_char);
        res[index] = this->curr_char;
        Lexer_advance(this);
        index++;
    }

    res[index] = '\0';
    return res;
}

void Lexer_whitespace(struct Lexer *this) {
    while (this->curr_char != '\0' && isspace(this->curr_char)) {
        Lexer_advance(this);
    }
}

struct Token* Lexer_get_next_token(struct Lexer *this) {
    while (this->curr_char != '\0') {

        if (isspace(this->curr_char)) {
            Lexer_whitespace(this);
            continue;
        }


        if (isdigit(this->curr_char)) {
                struct Token *ret = malloc(sizeof(struct Token));
                enum token_type t = INTEGER;
                // Lexer_integer(this, &(ret->value));
                init_Token_types(ret, t, Lexer_integer(this, ret->value));
                // Lexer_advance(this);
                return ret;
        }

        if (this->curr_char == '+') {
                struct Token *ret = malloc(sizeof(struct Token));
                enum token_type t = ADD;
                init_Token_types(ret, t, "+");
                Lexer_advance(this);
                return ret;
        }

        if (this->curr_char == '-') {
                struct Token *ret = malloc(sizeof(struct Token));
                enum token_type t = MINUS;
                init_Token_types(ret, t, "-");
                Lexer_advance(this);
                return ret;
        }

        if (this->curr_char == '*') {
            struct Token *ret = malloc(sizeof(struct Token));
            enum token_type t = MULT;
            init_Token_types(ret, t, "*");
            Lexer_advance(this);
            return ret;
        }

        if (this->curr_char == '/') {
            struct Token *ret = malloc(sizeof(struct Token));
            enum token_type t = DIV;
            init_Token_types(ret, t, "/");
            Lexer_advance(this);
            return ret;
        }
        if (this->curr_char == '(') {
            struct Token *ret = malloc(sizeof(struct Token));
            enum token_type t = LPARENT;
            init_Token_types(ret, t, "(");
            Lexer_advance(this);
            return ret;
        }
        
    if (this->curr_char == ')') {
            struct Token *ret = malloc(sizeof(struct Token));
            enum token_type t = RPARENT;
            init_Token_types(ret, t, ")");
            Lexer_advance(this);
            return ret;
        }
    }

    struct Token *ret = malloc(sizeof(struct Token));
    enum token_type t = END;
    init_Token_types(ret, END, "E");
    return ret;

}
