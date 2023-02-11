#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

struct Lexer {
    char text[300];
    int pos;
    struct Token curr_token;
    char curr_char;

};

void init_Lexer_types(struct Lexer *this) { // constructor for Lexer
    // memcpy (this->text, i, strlen(i));
    this->pos = 0;
    this->curr_char = this->text[0];
}

void Lexer_advance(struct Lexer *this) {  // helper function for next_token
    this->pos += 1;
    this->curr_char = this->text[this->pos];
}

// void Lexer_integer(struct Lexer *this, char **res) {
//     int index = 0;
//     while (this->curr_char != '\0' && isdigit(this->curr_char)) {
//         *res[index] = this->curr_char;
//         Lexer_advance(this);
//         index++;
//     }

// }

void Lexer_whitespace(struct Lexer *this) {
    while (this->curr_char != '\0' && isspace(this->curr_char)) {
        Lexer_advance(this);
    }
}

struct Token* Lexer_next_token(struct Lexer *this) {
    // if (this->pos > (sizeof(this->text)/sizeof(this->text[0]))) {
    //     struct Token *ret = malloc(sizeof(struct Token));
    //     enum token_type t = END;
    //     init_Token_types(ret, t, 'E');
    //     return ret;
    // } 
    printf("cc: %c\n", this->curr_char);
    while (this->curr_char != '\0') {

        if (isspace(this->curr_char)) {
            Lexer_whitespace(this);
            continue;
        }


        if (isdigit(this->curr_char)) {
                struct Token *ret = malloc(sizeof(struct Token));
                enum token_type t = INTEGER;
                // Lexer_integer(this, &(ret->value));
                init_Token_types(ret, t, &this->curr_char);
                Lexer_advance(this);
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
    }

    struct Token *ret = malloc(sizeof(struct Token));
    enum token_type t = END;
    init_Token_types(ret, END, "E");
    return ret;

}

void Lexer_eat_token(struct Lexer *this, enum token_type t) {
    printf("%u and %s\n", this->curr_token.type, this->curr_token.value);
    if (this->curr_token.type == t) {
        this->curr_token = *Lexer_next_token(this);
    } else {
       printf("token cannot be eaten!\n"); 
    }
}

int expr(struct Lexer *this) {
    this->curr_token = *Lexer_next_token(this);

    struct Token left = this->curr_token;
    
    Lexer_eat_token(this, INTEGER);

    struct Token op = this->curr_token;
    if (op.type == 1) {
        Lexer_eat_token(this, ADD);
    } else {
        Lexer_eat_token(this, MINUS);
    }

    struct Token right = this->curr_token;
    Lexer_eat_token(this, INTEGER);
    int result;
    if (op.type == 1) {    
        result = atoi(left.value) + atoi(right.value);
    } else {
        result = atoi(left.value) - atoi(right.value);
    }


    return result;


}



int main() {
    char in[301];
    in[300] = '\0';

    // struct Lexer *lexer = malloc(sizeof(struct Lexer));
    struct Lexer lexer;
    printf("Enter expression: ");
    fgets(lexer.text, sizeof(in) - 1, stdin);
    
    printf("%s", in);

    init_Lexer_types(&lexer);

    printf("%s", lexer.text);

    int res = expr(&lexer);

    printf("%d", res);

    return 0;
}