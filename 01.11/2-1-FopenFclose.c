#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  if (f != NULL) {
    fclose(f);
  } else {
    perror("can't open input file");
  }
}
