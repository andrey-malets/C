#include <stdlib.h>

struct yield_ctx;

struct yield_ctx *get_yield_ctx(int _yield_h, int _yield_l);
void yield_impl(struct yield_ctx *ctx, void *value);

struct yield_ctx *init_yield_ctx(void *buf, size_t size,
                                 void (*yieldfn)());
void yield_swap(struct yield_ctx *ctx);
int yield_more(struct yield_ctx *ctx);
void *get_yield_value(struct yield_ctx *ctx);

#define YIELD_FUNC(fn) void fn(int _yield_h, int _yield_l)

#define YIELD(value) \
  yield_impl(get_yield_ctx(_yield_h, _yield_l), &value)

#define FOR_EACH(type, value, fn, buf_size, code) \
  { \
    char _yield_buf[buf_size]; \
    struct yield_ctx *_yield_ctx = \
        init_yield_ctx(_yield_buf, buf_size, fn); \
    for (yield_swap(_yield_ctx); \
         yield_more(_yield_ctx); \
         yield_swap(_yield_ctx)) { \
      type value = *((type *)get_yield_value(_yield_ctx)); \
      do { code } while (0); \
    } \
  }
