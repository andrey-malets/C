#include <stdio.h>

int f(int x) {
  static int y = 1;
  return x + y++;
}

int g(int x) {
  static int y = 10;
  return x + y++;
}

int main(void) {
  printf("%d\n", f(1));
  printf("%d\n", f(1));

  printf("%d\n", g(1));
  printf("%d\n", g(1));
}
