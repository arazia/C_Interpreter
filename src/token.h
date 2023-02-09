/* 
 * This file defines the token types a Parser will process
 */

enum token_type {
  INTEGER,
  ADD,
  END,
  ERROR
};

struct Token {
   enum token_type type;
   char value;
};

void init_Token_types(struct Token *this, enum token_type _type, char _value);