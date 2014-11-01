#include <stdio.h>

int main(void) {
  int count;
  char string[10];

  // if (scanf("%i", &count) == 1) {
  //   printf("integer: %d\n", count);
  // }

  if (scanf("%d", &count) == 1) {
    printf("decimal: %d\n", count);
  }

  if (scanf("%x", &count) == 1) {
    printf("hex: %x\n", count);
  }

  // if (scanf("%10s", string) == 1) {
  // if (scanf("%s", string) == 1) {
  //   puts(string);
  // }

  if (scanf(" %10c", string) == 1) {
    printf("%.10s", string);
  }
}
