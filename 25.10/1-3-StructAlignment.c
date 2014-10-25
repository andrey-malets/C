#include <inttypes.h>

struct First {
  int32_t x;
  int64_t y;
  // int32_t z;
};

struct Second {
  int64_t y;
  int32_t x;
  // int32_t z;
};

int main(void) {
  return sizeof(struct First) - sizeof(struct Second);
}
