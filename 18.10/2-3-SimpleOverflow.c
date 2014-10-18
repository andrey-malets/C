#include <stdio.h>

int main(void) {
  char buffer[10];

  gets(buffer);
  puts(buffer);

  return 0;
}
