#include <stdio.h>

int f(int x) {
  printf("%d\n", x);
  return x+2; 
}

int g(int x) {
  return f(++x) * f(x++);
  // return f(x++) * f(++x);
}

int main(void) {
  return g(2);
}
