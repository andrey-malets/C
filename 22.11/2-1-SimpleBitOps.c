#include <assert.h>
#include <stdio.h>

#define O_READ   0x1
#define O_WRITE  0x2
#define O_APPEND 0x4
#define O_BINARY 0x8

void open(int mode) {
  assert(!((mode & O_WRITE) && (mode & O_APPEND)));

#define DUMP(flag, msg) \
  if (mode & flag) \
    printf("%7s: 0x%x\n", msg, flag);
  DUMP(mode,     "all");
  DUMP(O_READ,   "read");
  DUMP(O_WRITE,  "write");
  DUMP(O_APPEND, "append");
  DUMP(O_BINARY, "binary");
#undef DUMP

  puts("");
}

int main(void) {
  int mode = O_READ | O_WRITE | O_BINARY;
  open(mode);

  // mode &= ~O_WRITE;
  mode |= O_APPEND;
  open(mode);
}
