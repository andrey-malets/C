#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *f = fopen(__FILE__, "r");
  if (!f) {
    perror("can't open input file");
    exit(1);
  }

  int c;
  while ((c = fgetc(f)) != EOF) {
    fputc(c, stdout);
  }

  // char buf[20];
  // size_t size;
  // while ((size = fread(buf, 1, sizeof(buf), f)) > 0) {
  //   fwrite(buf, 1, size, stdout);
  // }

  fclose(f);
  exit(0);
}

/////////////////////////////////////////////////////
