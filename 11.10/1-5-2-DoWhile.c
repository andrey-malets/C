#include <stdio.h>

int main(void) {
  short x = 0;
  short y = 0;

  do {
    x = y;
    y = x + 1;
  } while (y > x);

  printf("%d\n", x);
  return 0;
}
