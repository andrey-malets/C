#include <stdio.h>

int interesting(int value) {
  return (value % 42) == 7;
}

int should_stop(int value) {
  return (value % 42) == 10;
}

void process(int value) {
  printf("got %d", value);
}

int main(void) {
  for (size_t value = 30; value != 50; ++value) {
    if (should_stop(value)) {
      break;
    }
    if (!interesting(value)) {
      continue;
    }
    process(value);
  }

  return 0;
}
