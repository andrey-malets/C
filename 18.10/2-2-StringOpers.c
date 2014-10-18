#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t mystrlen(const char *str) {
  size_t rv = 0;
  for (; *str; ++str)
    ++rv;
  return rv;
}

char *mystpcpy(char *dst, const char *src) {
  while ((*dst++ = *src++))
    ;
  return --dst;
}

int main(void) {
  const char str[] = "longstring";

  char copy[11];
  const char* rv = mystpcpy(copy, str);
  puts(copy);

  return mystrlen(str) - (rv - copy);
}

// P.S.
// http://www.joelonsoftware.com/articles/CollegeAdvice.html
// http://www.joelonsoftware.com/articles/fog0000000319.html
