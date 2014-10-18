#include <stdio.h>

int main(void) {
  int x, y;
  int *px = &x;

  x = 10;   printf("%d %d\n", *px, x);
  x = 20;   printf("%d %d\n", *px, x);
  *px = 30; printf("%d %d\n", *px, x);

  px = &y;  printf("%d %d\n", *px, y);

  px = x;   printf("%d %d\n", *px, *px);

  return 0;
}
