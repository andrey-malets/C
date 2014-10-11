#include <stdio.h>

#define LOG(level, string) \
do { \
  if (level <= LOG_LEVEL) \
    fputs(string "\n", stderr); \
} while (0)

int *get_ptr(int value) {
  return (int *)42;
}

#define LOG_LEVEL 0

int main(void) {
  int value;
  int *pvalue = get_ptr(value);

  LOG(1, "got pvalue, let's use it");
  *pvalue = 0;

  LOG(0, "OK, about to return");
  return 0;
}
