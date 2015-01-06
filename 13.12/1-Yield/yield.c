#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include "conv.h"
#include "yield.h"

#include <assert.h>
#include <stdlib.h>
#include <ucontext.h>

// clang_opts: -Wno-deprecated-declarations

struct yield_ctx {
  ucontext_t caller;
  ucontext_t callee;
  void *value;
  char stack[];
};

struct yield_ctx *get_yield_ctx(int h, int l) {
  return make_ptr(h, l);
}

void yield_impl(struct yield_ctx *ctx, void *value) {
  ctx->value = value;
  swapcontext(&ctx->callee, &ctx->caller);
  ctx->value = 0;
}

struct yield_ctx *init_yield_ctx(void *buf, size_t buf_size,
                                 void (*yieldfn)()) {
  assert(buf);
  assert(buf_size > sizeof(struct yield_ctx));

  struct yield_ctx *rv = buf;
  rv->value = 0;

  getcontext(&rv->callee);
  rv->callee.uc_link = &rv->caller;
  rv->callee.uc_stack.ss_sp = &rv->stack;
  rv->callee.uc_stack.ss_size = buf_size - sizeof(struct yield_ctx);
#ifdef __APPLE__
  assert(rv->callee.uc_stack.ss_size >= 32*1024);
#endif
  makecontext(&rv->callee, yieldfn, 2, get_high(rv), get_low(rv));
  return rv;
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
