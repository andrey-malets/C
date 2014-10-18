#include <stdio.h>

void swap(int x, int y) {
  int tmp = x;
  x = y;
  y = tmp;
}

void swap2(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

int main(void) {
  int x = 1, y = 2;
  printf("%d %d\n", x, y);

  swap(x, y);
  printf("%d %d\n", x, y);

  swap2(&x, &y);
  printf("%d %d\n", x, y);

  return 0;
}
