#ifndef TOKEN_H
#define TOKEN_H


/* 
 * This file defines the token types a Parser will process
 */


enum token_type {
  INTEGER,
  ADD,
  MINUS,
  MULT,
  DIV,
  END,
  ERROR
};

struct Token {
   enum token_type type;
   char value[20];
};

void init_Token_types(struct Token *this, enum token_type _type, char _value[]);

#endif