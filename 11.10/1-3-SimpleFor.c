#include <stdlib.h>

int main(void) {
  int x[] = {1, 2, 3, 4, 5};
  int sum = 0;

  for (size_t i = 0; i < 5; ++i)
    sum += x[i];
  return sum;
}
