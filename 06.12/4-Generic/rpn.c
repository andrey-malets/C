#include <assert.h>

#include "rpn.h"
#include "stack.h"

DECLARE_STACK(int)
DECLARE_STACK(char)

struct Token GetOp(char c) {
  return (struct Token) { .data.op = c, .type = T_OP };
}

struct Token GetNum(int num) {
  return (struct Token) { .data.num = num, .type = T_NUM };
}

int calculate(struct Token *tokens, size_t size) {
  STACK_OF(int) *stack = STACK_F(allocate, int)(10);
  for (size_t i = 0; i != size; ++i) {
    int rhs, lhs, rv;
    switch (tokens[i].type) {
    case T_NUM:
      STACK_F(push, int)(stack, tokens[i].data.num);
      break;
    case T_OP:
      rhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
      lhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
      switch (tokens[i].data.op) {
      case '+':
        rv = lhs + rhs;
        break;
      case '*':
        rv = lhs * rhs;
        break;
      default:
        assert(0);
        break;
      }
      STACK_F(push, int)(stack, rv);
      break;
    default:
      assert(0);
      break;
    }
  }
  int rv = STACK_F(top, int)(stack);
  STACK_F(deallocate, int)(stack);
  return rv;
}
