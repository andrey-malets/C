#include <assert.h>
#include <stdlib.h>

#define arraysize(x) sizeof(x)/sizeof(x[0])

#define GLOBAL_SIZE (1024*1024)
int GLOBAL[GLOBAL_SIZE];

int main(void) {
  size_t local_size = arraysize(GLOBAL);
  int local[local_size];

  for (size_t i = 0; i != arraysize(GLOBAL); ++i)
    assert(!GLOBAL[i]);
  for (size_t i = 0; i != local_size; ++i)
    assert(!local[i]);

  // for (size_t i = 0; i != arraysize(GLOBAL); ++i)
  //   GLOBAL[i] = 0;
  // for (size_t i = 0; i != local_size; ++i)
  //   local[i] = 0;
}
