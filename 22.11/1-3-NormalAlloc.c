#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

// suffix: <<<"2 1 2 10 20"

void do_stuff(int64_t** values, size_t n) {
  for (size_t i = 0; i != n; ++i) {
    printf("%"PRIi64" %"PRIi64" ", values[i][0], values[i][1]);
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

  int64_t **values = malloc(n * sizeof(int64_t*));
  CHECK(values, free_all, rv, 1);

  size_t allocated = 0;
  for (size_t i = 0; i != n; allocated = ++i) {
    int64_t x, y;
    scanf("%"SCNi64" %"SCNi64, &x, &y);

    values[i] = malloc(2 * sizeof(int64_t));
    CHECK(values[i], free_by_one, rv, 2);

    values[i][0] = x;
    values[i][1] = y;
  }

  do_stuff(values, n);

free_by_one:
  for (size_t i = 0; i != allocated; ++i)
    free(values[i]);

free_all:
  free(values);
  return rv;
}
