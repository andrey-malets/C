#include <stdio.h>

int main(void) {
  int x = 10, y = 20, z = 30;
  int arr[] = {1, 2, 3};

  int *ptrs[] = {&x, &y, &z, &arr[1]};

  for (size_t i = 0; i != sizeof(ptrs)/sizeof(ptrs[0]); ++i) {
    printf("%d ", *ptrs[i]);
  }
  puts("\n");

  return 0;
}
