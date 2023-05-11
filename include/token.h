#ifndef TOKEN_H
#define TOKEN_H


/* 
 * This file defines the token types a Parser will process
 */


enum token_type {
  INTEGER, // 0
  ADD, // 1
  MINUS, // 2
  MULT, // 3
  DIV, // 4
  LPARENT, // 5
  RPARENT, // 6
  END, // 7
  ERROR // 8
};

struct Token {
   enum token_type type;
   char value[20];
};

void init_Token_types(struct Token *self, enum token_type _type, char _value[]);

#endif