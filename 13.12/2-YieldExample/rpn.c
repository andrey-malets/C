#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "rpn.h"
#include "stack.h"
#include "yield.h"

DECLARE_STACK(int)
DECLARE_STACK(char)

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

static struct Token get_op(char c) {
  return (struct Token) { .data.op = c, .type = T_OP };
}

static struct Token get_num(int num) {
  return (struct Token) { .data.num = num, .type = T_NUM };
}

static struct Token get_token(const char *token_str) {
  return isdigit(token_str[0]) ?
      get_num(atoi(token_str)) :
      get_op(token_str[0]);
}

static int apply_op(int lhs, int rhs, char op) {
  switch (op) {
    case '+': return lhs + rhs;
    case '-': return lhs - rhs;
    case '*': return lhs * rhs;
    case '/': return lhs / rhs;
    default: assert(0);
  }
}

static int prio(char op) {
  switch (op) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: assert(0);
  }
}

#define YIELD_FROM(ops) { \
  struct Token op = get_op(STACK_F(top, char)(ops)); \
  YIELD(op); \
  STACK_F(pop, char)(ops); \
}
YIELD_FUNC(collect) {
  STACK_OF(char) *ops = STACK_F(allocate, char)(10);
  char token_str[10];
  while (scanf("%10s", token_str) == 1) {
    struct Token token = get_token(token_str);
    switch (token.type) {
    case T_NUM:
      YIELD(token);
      break;
    case T_OP:
      while (!STACK_F(empty, char)(ops) &&
             prio(STACK_F(top, char)(ops)) >= prio(token.data.op)) {
        YIELD_FROM(ops);
      }
      STACK_F(push, char)(ops, token.data.op);
      break;
    default:
      assert(0);
      break;
    }
  }

  while (!STACK_F(empty, char)(ops))
    YIELD_FROM(ops);

  STACK_F(deallocate, char)(ops);
}
#undef YIELD_FROM

void process(STACK_OF(int) *stack, struct Token token) {
  int rhs, lhs;
  switch (token.type) {
  case T_NUM:
    STACK_F(push, int)(stack, token.data.num);
    break;
  case T_OP:
    rhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
    lhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
    STACK_F(push, int)(stack, apply_op(lhs, rhs, token.data.op));
    break;
  default:
    assert(0);
    break;
  }
}

int calculate() {
  STACK_OF(int) *stack = STACK_F(allocate, int)(10);

  FOR_EACH(struct Token, token, collect, 2048+32*1024,
    process(stack, token);
  );

  int rv = STACK_F(top, int)(stack);
  STACK_F(deallocate, int)(stack);
  return rv;
}
