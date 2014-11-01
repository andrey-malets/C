#include <stdio.h>

int main(void) {
  char msg[10];
  double big_num;

  if (sscanf("1e10", "%lf", &big_num) != 1) {
    return 2;
  }

  int size = snprintf(msg, sizeof(msg), "%.1lf", big_num);
  puts(msg);
  return size > sizeof(msg);
}
