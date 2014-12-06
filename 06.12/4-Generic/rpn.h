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

size_t collect(struct Token *output, size_t max_size);
int calculate(struct Token *tokens, size_t size);

void dump(struct Token *tokens, size_t size);
