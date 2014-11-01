#include <stdio.h>

int main(void) {
  int c = getchar();
  if (c != EOF) {
    return putchar(c) != c;
  } else {
    return 1;
  }
}
