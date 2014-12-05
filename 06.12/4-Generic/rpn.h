#include <stdlib.h>

enum TokenType {
  T_OP,
  T_NUM
};

struct Token {
  union Data {
    char op;
    int num;
  } data;

  int type;
};

int calculate(struct Token *tokens, size_t size);
