#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

#define static_assert _Static_assert

// clang_opts: -std=c11

struct Descriptor {
  unsigned base  : 13;
  unsigned type  : 2;
  unsigned valid : 1;
  int      index : 16;
};

enum Type {
  T_UNDEFINED,
  T_SYSTEM,
  T_SERVICE,
  T_USER
};

void dump(struct Descriptor descr) {
  static_assert(sizeof(struct Descriptor) == 4,
                "we expect this struct to occupy exactly 4 bytes");
  int32_t *raw = (int32_t *)&descr;
  printf("raw:   %x\n", *raw);
  printf("base:  %u\n", descr.base);
  printf("type:  %u\n", descr.type);
  printf("valid: %s\n", descr.valid ? "true" : "false");
  printf("index: %d\n", descr.index);
  puts("");
}

int main(void) {
  struct Descriptor descriptor = {
    1024,
    T_SERVICE,
    1,
    -256
  };
  dump(descriptor);

  descriptor.index >>= 3;
  dump(descriptor);

  descriptor.valid = 0;
  dump(descriptor);

  return 0;
}
