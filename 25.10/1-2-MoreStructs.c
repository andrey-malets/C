#include <stdio.h>

struct RV {
  unsigned result;
  int      error;
};

struct RV do_stuff(int x, int y) {
  // struct RV rv = { .error = 0 };
  // struct RV rv = { 0, 0 };
  // struct RV rv = { 0 };
  struct RV rv;
  if (x >= y) {
    rv.result = x - y;
  } else {
    rv.error = 1;
  }
  return rv;
}

int main(void) {
  struct RV rv = do_stuff(10, 20);
  // struct RV rv = do_stuff(20, 10);
  if (!rv.error) {
    printf("%u\n", rv.result);
  }
  return rv.error;
}
