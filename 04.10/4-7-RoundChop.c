#include <inttypes.h>

int main(void) {
  uint16_t big_value = UINT16_MAX;
  uint8_t does_not_fit = big_value;

  return does_not_fit == big_value;

  // return 9/10;
}
