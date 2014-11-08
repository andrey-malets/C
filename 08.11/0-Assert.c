#include <assert.h>
#include <stdlib.h>

// clang_opts: -std=c11

#define static_assert _Static_assert
typedef long my_super_type;
static_assert(sizeof(my_super_type) > 4,
              "can't operate with too small numbers");

int main(int argc, char *argv[]) {
  assert(argc >= 2);
  assert(argv[1]);
  return atol(argv[1]);
}
