#include "conv.h"

#include <assert.h>

// clang_opts: -std=c1x

_Static_assert(sizeof(void *) == sizeof(unsigned long),
               "not implemented yet for non-64-bit machines");

_Static_assert(sizeof(int)*2 == sizeof(unsigned long),
               "not implemented yet for non-64-bit machines");

int get_high(void *ptr) {
  unsigned long value = (unsigned long) ptr;
  return value >> 32;
}

int get_low(void *ptr) {
  unsigned long value = (unsigned long) ptr;
  return value & 0xFFFFFFFFl;
}

void *make_ptr(int h, int l) {
  unsigned high = h, low = l;
  unsigned long lhigh = high, llow = low;
  return (void *) (lhigh << 32 | llow);
}
