#include <inttypes.h>
#include <stdio.h>
#include <stdarg.h>

void dump(uint8_t value) {
  char buf[8];
  for (size_t i = 0; i != 8; ++i) {
    buf[i] = value & 1 << (8-i-1) ? '1' : '0';
  }
  printf("%.8s ", buf);
}

int main(void) {
  int8_t pos = 6, neg = -6;
  uint8_t u = 6;

#define PUT(p, n, u) do { \
  dump(p); dump(n); dump(u); \
  puts(""); \
} while (0)

  PUT(pos, neg, u);
  PUT(pos << 1, neg << 1, u << 1);
  PUT(pos >> 1, neg >> 1, u >> 1);
  PUT(pos >> 8, neg >> 8, u >> 8);

#undef PUT
}
