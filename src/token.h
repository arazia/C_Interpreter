#ifndef TOKEN_H
#define TOKEN_H


/* 
 * This file defines the token types a Parser will process
 */


enum token_type {
  INTEGER, // 1
  ADD, // 2
  MINUS, // 3
  MULT, // 4
  DIV, // 5
  LPARENT, // 6
  RPARENT, // 7
  END, // 8
  ERROR // 9
};

struct Token {
   enum token_type type;
   char value[20];
};

void init_Token_types(struct Token *this, enum token_type _type, char _value[]);

#endif