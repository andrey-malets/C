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

int main(void) {
  size_t n;
  scanf("%zu", &n);

  int64_t **values = malloc(n * sizeof(int64_t*));
  if (!values) {
    return 1;
  }

  for (size_t i = 0; i != n; ++i) {
    int64_t x, y;
    scanf("%"SCNi64" %"SCNi64, &x, &y);
    values[i] = malloc(2 * sizeof(int64_t));
    if (!values[i]) {
      for (size_t j = 0; j != i; ++j) {
        free(values[i]);
      }
      free(values);
      return 2;
    }
    values[i][0] = x;
    values[i][1] = y;
  }

  do_stuff(values, n);

  for (size_t i = 0; i != n; ++i) {
    free(values[i]);
  }
  free(values);
  return 0;
}
