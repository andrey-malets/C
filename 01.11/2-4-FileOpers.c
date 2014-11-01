#include <stdio.h>
#include <stdlib.h>

void check(int rv, const char *msg) {
  if (!rv) {
    perror(msg);
    exit(1);
  }
}

int main(void) {
  FILE *f = fopen(__FILE__, "r");
  check(f != NULL, "open input file");
  check(fseek(f, 0, SEEK_END) == 0, "seek to the end");
  long pos = ftell(f);
  check(pos != -1, "tell position at the end");
  check(fclose(f) == 0, "close input file");

  printf("%ld\n", pos);
}
