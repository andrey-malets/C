#include "yield.h"

#include <stdlib.h>
#include <ucontext.h>

struct yield_ctx {
  ucontext_t caller;
  ucontext_t callee;
  void *value;
  char stack[];
};

struct yield_ctx *get_yield_ctx(int h, int l) {
  return (void *)(((unsigned long)h) << 32 | ((unsigned long)l));
}

void yield_impl(struct yield_ctx *ctx, void *value) {
  ctx->value = value;
  swapcontext(&ctx->callee, &ctx->caller);
  ctx->value = 0;
}

struct yield_ctx *init_yield_ctx(size_t stack_size,
                                 void (*yieldfn)()) {
  struct yield_ctx *rv = malloc(sizeof(struct yield_ctx) +
                                stack_size);
  if (rv) {
    rv->value = 0;
    getcontext(&rv->callee);
    rv->callee.uc_link = &rv->caller;
    rv->callee.uc_stack.ss_sp = &rv->stack;
    rv->callee.uc_stack.ss_size = stack_size;
    makecontext(&rv->callee,
                yieldfn,
                2,
                (int)((long)rv >> 32),
                (int)((long)rv & 0xFFFFFFFF));
  }
  return rv;
}

void free_yield_ctx(struct yield_ctx *ctx) {
  free(ctx);
}

void yield_swap(struct yield_ctx *ctx) {
  swapcontext(&ctx->caller, &ctx->callee);
}

int yield_more(struct yield_ctx *ctx) {
  return ctx->value != 0;
}

void *get_yield_value(struct yield_ctx *ctx) {
  return ctx->value;
}
