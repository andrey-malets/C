#include <stdio.h>

int main(void) {
  int x = 10, y = 20;
  int *px = &x, *py = &y;

  int **pp = &px;

  *px = 30;
  *py = 40;

  pp = &py;
  *pp = &x;
  **pp = 50;

  printf("%d %d\n", x, y);
  printf("%p %p\n", px, py);
  return 0;
}
