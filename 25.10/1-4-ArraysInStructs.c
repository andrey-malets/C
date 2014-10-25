#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t size;
  int values[];
} SimpleArray;

SimpleArray *allocate(size_t n) {
  SimpleArray *rv = NULL;
  if ((rv = malloc(sizeof(SimpleArray) + n * sizeof(int)))) {
    rv->size = n * sizeof(int);
  }
  return rv;
}

void process(SimpleArray *arr) {
  assert(arr);
  for (size_t i = 0; i != arr->size; ++i) {
    arr->values[i] = i;
  }
}

void output(SimpleArray *arr) {
  assert(arr);
  for (size_t i = 0; i != arr->size; ++i) {
    printf(i == arr->size - 1 ? "%d\n" : "%d ",
           arr->values[i]);
  }
}

void deallocate(SimpleArray *arr) {
  free(arr);
}

int main(void) {
  size_t size = 20;
  SimpleArray *array = allocate(size);
  if (array) {
    process(array);
    output(array);
  }
  int rv = array != NULL;
  deallocate(array);
  return rv ? 0 : 1;
}
