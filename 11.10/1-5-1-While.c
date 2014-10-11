#include <stdio.h>

int main(void) {
  short x = 0;
  short y = x + 1;

  while (y > x) {
    x = y;
    y = y + 1;
  }

  printf("%d\n", x);
  return 0;
}
