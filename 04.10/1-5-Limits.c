#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
  printf("%"PRId16"\n", INT16_MAX);
  printf("%"PRId16"\n", INT32_MIN);
  printf("%"PRId16"\n", INT64_MAX);
  return 0;
}
