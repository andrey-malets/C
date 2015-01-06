#include "yield.h"

#include <stdio.h>

YIELD_FUNC(first_ten_fibs) {
  unsigned a = 0, b = 1;
  for (size_t i = 0; i != 10; ++i) {
    YIELD(a);
    unsigned pa = a;
    a = b;
    b = pa + b;
  }
}

int main(void) {
  FOR_EACH(unsigned, fibn, first_ten_fibs, 2048+32*1024,
    printf("%u\n", fibn);
  )

  return 0;
}
