#include <assert.h>

int is_power_of_2(unsigned x) {
  return !(x & (x-1));
}

unsigned flp2(unsigned x) {
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >>16);
  return x - (x >> 1);
}

#define TEST(func, value, res) \
  assert(func(value) == res);

void test_power_of_2(void) {
  TEST(is_power_of_2, 4, 1);
  TEST(is_power_of_2, 32768, 1);

  TEST(is_power_of_2, 10, 0);
  TEST(is_power_of_2, 31337, 0);
}

void test_flp2(void) {
  TEST(flp2, 1,  1);
  TEST(flp2, 10, 8);
  TEST(flp2, 17, 16);
  TEST(flp2, 32, 32);
  TEST(flp2, 48, 32);
  TEST(flp2, 16384, 16384);
}

int main(void) {
  test_power_of_2();
  test_flp2();
}

// http://www.hackersdelight.org/
