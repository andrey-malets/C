#include "rpn.h"

int main(void) {
  struct Token tokens[100];
  size_t ntokens = collect(tokens, sizeof(tokens)/sizeof(struct Token));
  return calculate(tokens, ntokens);
}
