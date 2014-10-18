#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t count = 5;
  size_t big_count = 20;

  long *arr = calloc(count, sizeof(long));
  for (size_t i = 0; i != count; ++i) {
    printf("%ld ", arr[i]);
  }
  puts("");

  arr = realloc(arr, big_count);
  for (size_t i = 0; i != big_count; ++i) {
    printf("%ld ", arr[i]);
  }
  puts("");

  free(arr);

  return 0;
}
