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

void init_Lexer_types(struct Lexer *this, char i[]) { // constructor for Lexer
    memcpy (this->text, i, strlen(i)+1);
    this->pos = 0;
}

struct Token* Lexer_next_token(struct Lexer *this) {
    if (this->pos > (sizeof(this->text)/sizeof(this->text[0]))) {
        struct Token *ret = malloc(sizeof(struct Token));
        enum token_type t = END;
        init_Token_types(ret, t, 'E');
        return ret;
    } 
    
    this->curr_char = this->text[this->pos];

    if (isdigit(this->curr_char)) {
        struct Token *ret = malloc(sizeof(struct Token));
        enum token_type t = INTEGER;
        init_Token_types(ret, t, this->curr_char);
        this->pos += 1;
        return ret;
    }

    if (this->curr_char == '+') {
        struct Token *ret = malloc(sizeof(struct Token));
        enum token_type t = ADD;
        init_Token_types(ret, t, this->curr_char);
        this->pos += 1;
        return ret;
    }

    struct Token *ret = malloc(sizeof(struct Token));
    enum token_type t = ERROR;
    init_Token_types(ret, t, 'E');
    return ret;

}

void Lexer_eat_token(struct Lexer *this, enum token_type t) {
    if (this->curr_token.type == t) {
        this->curr_token = *Lexer_next_token(this);
    } else {
       printf("token cannot be eaten!"); 
    }
}

int expr(struct Lexer *this) {
    this->curr_token = *Lexer_next_token(this);

    struct Token left = this->curr_token;
    Lexer_eat_token(this, INTEGER);

    struct Token op = this->curr_token;
    Lexer_eat_token(this, ADD);

    struct Token right = this->curr_token;
    Lexer_eat_token(this, INTEGER);

    int result = (int)left.value + (int)right.value;

    return result;


}


int main() {
    char in[300];

    struct Lexer* lexer;

    printf("Enter expression: ");
    fgets(in, sizeof(in), stdin);

    init_Lexer_types(lexer, in);

    printf("%s", lexer->text);


    int res = expr(lexer);

    printf("%d", res);

    return 0;
}