#include <stdlib.h>

#include "stack.h"

DECLARE_STACK(int)
DECLARE_STACK(char)

int main(void) {
  STACK_OF(int) *numbers = STACK_F(allocate, int)(10);
  STACK_F(deallocate, int)(numbers);

  STACK_OF(char) *syms = STACK_F(allocate, char)(10);
  STACK_F(deallocate, char)(syms);
}
