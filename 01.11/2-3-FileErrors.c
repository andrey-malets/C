#include <stdio.h>
#include <stdlib.h>

void check(int rv, const char *msg) {
  if (!rv) {
    perror(msg);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");
  check(f != NULL, "open input");
  int c;
  while ((c = fgetc(f)) != EOF)
    ;

  check(ferror(f) == 0, "read input");
  check(fclose(f) == 0, "close input");
}
