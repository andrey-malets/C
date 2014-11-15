#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// clang_opts: -O2

int can_allocate(size_t bytes) {
  int rv = 1;
  char *buffer = malloc(bytes);
  if (!buffer) {
    rv = 0;
    goto free;
  }

  memset(buffer, 0, bytes);

  assert(buffer[0] == 0);
  assert(buffer[bytes-1] == 0);
  rv = 1;

free:
  free(buffer);
  return rv;
}

int main(void) {
  for (size_t size = 1; can_allocate(size); size <<= 1)
    printf("%zu\n", size);
  return 0;
}
