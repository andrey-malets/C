#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// suffix: <<<"2 1 2 10 20"

struct Value {
  int64_t index;
  int64_t score;
};

void do_stuff(struct Value values[], size_t n) {
  for (size_t i = 0; i != n; ++i) {
    printf("%"PRIi64" %"PRIi64" ",
          values[i].index, values[i].score);
  }
  puts("");
}

#define CHECK(cond, label, rv, value) do { \
  if (!(cond)) { \
    (rv) = (value); \
    goto label; \
  } \
} while (0)

int main(void) {
  int rv = 0;
  size_t n;
  scanf("%zu", &n);

  struct Value *values = malloc(n * sizeof(struct Value));
  CHECK(values, free_all, rv, 1);

  for (size_t i = 0; i != n; ++i)
    scanf("%"SCNi64" %"SCNi64,
          &values[i].index, &values[i].score);

  do_stuff(values, n);

free_all:
  free(values);
  return rv;
}
