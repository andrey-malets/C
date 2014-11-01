#include <stdio.h>
#include <inttypes.h>

int main(void) {
  int8_t small;
  int_fast64_t huge;

  scanf("%"SCNd8, &small);
  printf("%"PRIi8"\n", small);

  scanf("%"SCNiFAST64, &huge);
  printf("%"PRIiFAST64"\n", huge);
}
