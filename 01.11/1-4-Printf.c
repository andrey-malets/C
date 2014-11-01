#include <stdio.h>

int main(void) {
  int count = 90;
  const char string[] = "this is a string";

  printf("%d\n", count);
  printf("%10d\n", count);
  printf("%X\n", count);
  printf("0x%.8x\n", count);

  puts("");
  puts(string);

  printf("%s\n%10s\n%20s\n", string, string, string);
  printf("%p\n", string);
  printf("%.16p\n", string);
}
