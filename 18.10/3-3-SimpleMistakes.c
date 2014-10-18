#include <stdio.h>
#include <stdlib.h>

int main(void) {
  size_t count;
  scanf("%zu", &count);

  int *arr = malloc(count * sizeof(int));
  int sum = 0;

  for (size_t i = 0; i != count; ++i) {
    scanf("%d", &arr[i]);
  }

  for (size_t i = 0; i != count; ++i) {
    sum += arr[i];
  }

  free(arr);

  printf("%d\n", sum);
  return 0;
}
