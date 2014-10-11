#include <stdio.h>

enum ErrorCode {
  ERR_OK = 0,
  ERR_NOT_FOUND,
  ERR_PERM,
  ERR_UNK,
};

int do_some_buggy_stuff() {
  return ERR_PERM;
}

int main(void) {
  switch (do_some_buggy_stuff()) {
  case ERR_OK:
    break;
  case ERR_NOT_FOUND:
  case ERR_PERM:
    fputs("file error :(\n", stderr);
    return 1;
  default:
    fputs("totally unknown error O_o\n", stderr);
    return 10;
  }

  return 0;
}
