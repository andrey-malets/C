#include "rpn.h"

int main(void) {
  struct Token tokens[] = {
    { .type = T_NUM, .data.num = 1 },
    { .type = T_NUM, .data.num = 2 },
    { .type = T_OP,  .data.op = '+'},

    { .type = T_NUM, .data.num = 3 },
    { .type = T_NUM, .data.num = 4 },
    { .type = T_OP,  .data.op = '+'},

    { .type = T_OP,  .data.op = '*'}
  };

  return calculate(tokens, sizeof(tokens)/sizeof(struct Token));
}
