#include <stdio.h>

int main(void) {
  int x[] = {1, 2, 3};
  int y[] = {4, 5, 6, 7};

  int *px = &x[1];
  int *px2 = &x[2];
  int *py = &y[3];

  printf("%td\n", px2 - px);
  printf("%td\n", px - px2);
  printf("%td\n", px - py);

  printf("%d\n", *px);
  printf("%d\n", *(px + 1));
  printf("%d\n", *(px + 2));

  return 0;
}
