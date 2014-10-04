#include <inttypes.h>

int main(void) {
  uint8_t limit = UINT8_MAX;
  uint8_t push_the_limit = limit + 1;
  return push_the_limit == 0;
}
