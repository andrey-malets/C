#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "rpn.h"
#include "stack.h"

DECLARE_STACK(int)
DECLARE_STACK(char)

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

static void append_token(struct Token *output, size_t max_size,
                         size_t index, struct Token token) {
  assert(index < max_size);
  output[index] = token;
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

size_t collect(struct Token *output, size_t max_size) {
  STACK_OF(char) *ops = STACK_F(allocate, char)(10);
  char token_str[10];
  size_t rv = 0;
  while (scanf("%10s", token_str) == 1) {
    struct Token token = get_token(token_str);
    switch (token.type) {
    case T_NUM:
      append_token(output, max_size, rv++, token);
      break;
    case T_OP:
      while (!STACK_F(empty, char)(ops) &&
             prio(STACK_F(top, char)(ops)) >= prio(token.data.op)) {
        append_token(output, max_size, rv++, get_op(STACK_F(top, char)(ops)));
        STACK_F(pop, char)(ops);
      }
      STACK_F(push, char)(ops, token.data.op);
      break;
    default:
      assert(0);
      break;
    }
  }
  while (!STACK_F(empty, char)(ops)) {
    append_token(output, max_size, rv++, get_op(STACK_F(top, char)(ops)));
    STACK_F(pop, char)(ops);
  }
  STACK_F(deallocate, char)(ops);
  return rv;
}

int calculate(struct Token *tokens, size_t size) {
  STACK_OF(int) *stack = STACK_F(allocate, int)(10);
  for (size_t i = 0; i != size; ++i) {
    int rhs, lhs;
    switch (tokens[i].type) {
    case T_NUM:
      STACK_F(push, int)(stack, tokens[i].data.num);
      break;
    case T_OP:
      rhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
      lhs = STACK_F(top, int)(stack); STACK_F(pop, int)(stack);
      STACK_F(push, int)(stack, apply_op(lhs, rhs, tokens[i].data.op));
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

void dump(struct Token *tokens, size_t size) {
  for (size_t i = 0; i != size; ++i) {
    if (tokens[i].type == T_OP) {
      printf("%c", tokens[i].data.op);
    } else {
      assert(tokens[i].type == T_NUM);
      printf("%d", tokens[i].data.num);
    }
    fputs(i == size - 1 ? "\n" : " ", stdout);
  }
}
