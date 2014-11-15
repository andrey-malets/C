#include <assert.h>
#include <stdlib.h>

#define arraysize(x) sizeof(x)/sizeof(x[0])

int GLOBAL_VAR = 10;
int GLOBAL_ARRAY[10];

int f(int x) {
  return x + GLOBAL_VAR;
}

int main(void) {
  for (size_t i = 0; i != arraysize(GLOBAL_ARRAY); ++i)
    assert(!GLOBAL_ARRAY[i]);
  int x = 10;
  return f(x);
}
