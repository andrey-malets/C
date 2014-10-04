#include <stdint.h>

int main(void) {
  return sizeof(int8_t)   == 1 &&
         sizeof(uint8_t)  == 1 &&
         sizeof(int16_t)  == 2 &&
         sizeof(uint64_t) == 8;

  return sizeof(int_least16_t) >= 2;

  return sizeof(int_fast32_t);
}
