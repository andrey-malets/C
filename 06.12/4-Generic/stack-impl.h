#include <assert.h>
#include <stdlib.h>

#define STACK_ELEM STACK_TYPE()
#define STACK_IMPL STACK_TYPE(struct _stack_of_)
#define STACK_F(name) STACK_TYPE(_stack_f_ ## name ## _)

STACK_IMPL {
  size_t size;
  size_t pos;
  STACK_ELEM data[];
};

STACK_IMPL *STACK_F(allocate)(size_t size) {
  STACK_IMPL *rv = malloc(sizeof(STACK_IMPL) +
                          size * sizeof(STACK_ELEM));
  if (rv) {
    rv->size = size;
    rv->pos = 0;
  }
  return rv;
}

void STACK_F(deallocate)(STACK_IMPL *s) {
  free(s);
}

void STACK_F(push)(STACK_IMPL *s, STACK_ELEM e) {
  assert(s && s->pos < s->size);
  s->data[s->pos++] = e;
}

STACK_ELEM STACK_F(top)(STACK_IMPL *s) {
  assert(s && s->pos);
  return s->data[s->pos - 1];
}

void STACK_F(pop)(STACK_IMPL *s) {
  assert(s && s->pos);
  --s->pos;
}

int STACK_F(empty)(STACK_IMPL *s) {
  assert(s);
  return s->pos == 0;
}
