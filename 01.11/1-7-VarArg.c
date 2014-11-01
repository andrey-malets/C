#include <stdarg.h>
#include <stdio.h>

void print_ints(char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  while (*fmt) {
    switch (*fmt++) {
#define CASE(c,fmt,type,arg) \
    case c: printf("%" fmt "\n", va_arg(arg, type)); \
    break;

    CASE('d', "d",   int,   args);
    CASE('x', ".8x", int,   args);
    CASE('X', ".8X", int,   args);
    CASE('f', ".6f", double, args);

#undef CASE
    }
  }
  va_end(args);
}

int main(void) {
  print_ints("dXxf", 100, 200, 300, 400.05);
  return 0;
}
