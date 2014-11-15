#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// suffix: < 2-1-RectangularArray.input

struct RectArray {
  size_t rows, cols;
  int data[];
};

struct RectArray *AllocArray(size_t rows, size_t cols) {
  struct RectArray *res = malloc(sizeof(struct RectArray) +
                                 rows*cols*sizeof(int));
  if (res) {
    res->rows = rows;
    res->cols = cols;
  }
  return res;
}

void FreeArray(struct RectArray *arr) {
  free(arr);
}

int *GetElement(struct RectArray *arr, size_t i, size_t j) {
  assert(i < arr->rows);
  assert(j < arr->cols);
  return arr->data + (i*arr->cols + j);
}

int main(void) {
  size_t rows, cols;
  scanf("%zu %zu", &rows, &cols);
  struct RectArray *arr = AllocArray(rows, cols);
  if (!arr)
    goto free;

  for (size_t i = 0; i != arr->rows; ++i)
    for (size_t j = 0; j != arr->cols; ++j)
      scanf("%d", GetElement(arr, i, j));

  for (size_t i = 0; i != arr->rows; ++i)
    for (size_t j = 0; j != arr->cols; ++j)
      printf(j == arr->cols-1 ? "%d\n" : "%d ",
             *GetElement(arr, i, j));

  // for (size_t j = 0; j != arr->cols; ++j)
  //   for (size_t i = 0; i != arr->rows; ++i)
  //     printf(i == arr->rows-1 ? "%d\n" : "%d ",
  //            *GetElement(arr, i, j));
free:
  FreeArray(arr);
  return 0;
}
