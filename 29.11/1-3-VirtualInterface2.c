#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// clang_opts: -DNDEBUG

struct StackOps;

struct Stack {
  struct StackOps *ops;
};

#define ARROW0(ptr, op) (ptr->ops->op(ptr))
#define ARROWN(ptr, op, ...) (ptr->ops->op(ptr, __VA_ARGS__))

struct StackOps {
  struct Stack *(*allocate)(size_t size);
  void (*deallocate)(struct Stack *s);

  void (*push)(struct Stack *s, int value);
  void (*pop)(struct Stack *s);
  int  (*top)(struct Stack *s);
};

extern struct StackOps ArrayOps;
extern struct StackOps ListOps;

void test_ops(struct Stack *s) {
  size_t N = 10;
  assert(s);

  ARROWN(s, push, N);
  assert(ARROW0(s, top) == N);

  for (size_t i = 0; i != N; ++i) {
    ARROWN(s, push, i);
    assert(ARROW0(s, top) == i);
  }

  for (size_t i = N; i != 0; --i) {
    assert(ARROW0(s, top) == i - 1);
    ARROW0(s, pop);
  }
}

#define NEW_STACK(ops, N) (ops.allocate(N))

int main(void) {
  struct Stack *stacks[] = {NEW_STACK(ArrayOps, 20),
                            NEW_STACK(ListOps,  20)};
  for (size_t i = 0; i != sizeof(stacks)/sizeof(stacks[0]); ++i)
    test_ops(stacks[i]);

  for (size_t i = 0; i != sizeof(stacks)/sizeof(stacks[0]); ++i) {
    ARROW0(stacks[i], deallocate);
    stacks[i] = 0;
  }

  return 0;
}


// ----------------------------------------------


#ifndef NDEBUG
#define LOG(fmt, ...) do { \
  fprintf(stderr, "%s (%s:%u): ", __func__, __FILE__, __LINE__); \
  fprintf(stderr, fmt, __VA_ARGS__); \
  fputs("\n", stderr); \
} while (0)
#else
#define LOG(msg, ...)
#endif

#define RAW(ptr) ((char *)ptr)
#define UPCAST(type, basetype, ptr) \
  ((basetype *) (RAW(ptr) + offsetof(type, base)))
#define DOWNCAST(type, ptr) \
  ((type *) (RAW(ptr) - offsetof(type, base)))

struct ArrayStack {
  struct Stack base;

  size_t size;
  size_t pos;

  int data[];
};

struct Stack *array_allocate(size_t size) {
  LOG("size: %zu", size);
  struct ArrayStack *rv = malloc(sizeof(struct ArrayStack) +
                                 size*sizeof(int));
  if (rv) {
    rv->size = size;
    rv->pos = 0;
    rv->base.ops = &ArrayOps;
    return UPCAST(struct ArrayStack, struct Stack, rv);
  }
  return 0;
}

void array_deallocate(struct Stack *s) {
  LOG("%p", s);
  if (s) {
    free(DOWNCAST(struct ArrayStack, s));
  }
}

void array_push(struct Stack *s, int value) {
  struct ArrayStack *as = DOWNCAST(struct ArrayStack, s);
  assert(as->pos != as->size);
  as->data[as->pos++] = value;
}

void array_pop(struct Stack *s) {
  struct ArrayStack *as = DOWNCAST(struct ArrayStack, s);
  assert(as->pos);
  --as->pos;
}

int array_top(struct Stack *s) {
  struct ArrayStack *as = DOWNCAST(struct ArrayStack, s);
  assert(as->pos);
  return as->data[as->pos - 1];
}

struct StackOps ArrayOps = {
  .allocate   = array_allocate,
  .deallocate = array_deallocate,
  .push = array_push,
  .pop  = array_pop,
  .top  = array_top
};


// ----------------------------------------------


struct ListItem {
  struct ListItem *next;
  int value;
};

struct ListStack {
  struct Stack base;
  struct ListItem *head;
};

struct Stack *list_allocate(size_t size) {
  LOG("size: %zu", size);
  struct ListStack *rv = malloc(sizeof(struct ListStack));
  if (rv) {
    rv->head = 0;
    rv->base.ops = &ListOps;
    return UPCAST(struct ListStack, struct Stack, rv);
  }

  return 0;
}

void list_push(struct Stack *s, int value) {
  struct ListStack *ls = DOWNCAST(struct ListStack, s);
  struct ListItem *prev = ls->head;
  if ((ls->head = malloc(sizeof(struct ListItem)))) {
    ls->head->next = prev;
    ls->head->value = value;
  } else {
    ls->head = prev;
  }
  LOG("%p", ls->head);
}

int list_top(struct Stack *s) {
  struct ListStack *ls = DOWNCAST(struct ListStack, s);
  assert(ls->head);
  return ls->head->value;
}

void list_pop(struct Stack *s) {
  struct ListStack *ls = DOWNCAST(struct ListStack, s);
  assert(ls->head);
  LOG("%p", ls->head);
  struct ListItem *next = ls->head->next;
  free(ls->head);
  ls->head = next;
}

void list_deallocate(struct Stack *s) {
  LOG("%p", s);
  if (s) {
    struct ListStack *ls = DOWNCAST(struct ListStack, s);
    while (ls->head) {
      list_pop(UPCAST(struct ListStack, struct Stack, ls));
    }
    free(ls);
  }
}

struct StackOps ListOps = {
  .allocate   = list_allocate,
  .deallocate = list_deallocate,
  .push = list_push,
  .pop  = list_pop,
  .top  = list_top
};
