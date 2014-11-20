#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// suffix: < 2-2-NonRectangularArray.input

struct Comb {
  size_t rows;
  size_t size;
  int data[];
};

size_t *GetOffset(struct Comb *comb, size_t row) {
  size_t *start = (size_t *) comb->data;
  return start+row;
}

struct Comb *AllocComb(size_t rows, size_t size) {
  struct Comb *res = malloc(sizeof(struct Comb) +
                            rows*sizeof(size_t) +
                            size*sizeof(int));
  if (res) {
    res->rows = rows;
    res->size = size;
    memset(res->data, 0, rows);
    *GetOffset(res, 0) = 0;
  }
  return res;
}

void FreeComb(struct Comb *comb) {
  free(comb);
}

void AppendRow(struct Comb *comb, size_t row, size_t row_size) {
  assert(comb);
  assert(row < comb->rows);
  size_t next_offset = *GetOffset(comb, row) + row_size;
  if (row < comb->rows-1) {
    *GetOffset(comb, row+1) = next_offset;
  } else {
    assert(comb->size == next_offset);
  }
}

size_t GetRowLength(struct Comb *comb, size_t row) {
  if (row == comb->rows-1) {
    return comb->size - *GetOffset(comb, row);
  } else {
    return *GetOffset(comb, row+1) - *GetOffset(comb, row);
  }
}

int *GetStart(struct Comb *comb) {
  size_t *offset_start = (size_t *) comb->data;
  return (int *)(offset_start + comb->rows);
}

int *GetElement(struct Comb *comb, size_t row, size_t i) {
  return GetStart(comb) + *GetOffset(comb, row) + i;
}

int main(void) {
  size_t rows, size;
  scanf("%zu %zu", &rows, &size);
  struct Comb *comb = AllocComb(rows, size);
  if (!comb)
    goto free;
  for (size_t i = 0; i != rows; ++i) {
    size_t row_size;
    scanf("%zu", &row_size);
    AppendRow(comb, i, row_size);
    for (size_t j = 0; j != row_size; ++j) {
      int element;
      scanf("%d", &element);
      *GetElement(comb, i, j) = element;
    }
  }

  for (size_t i = 0; i != size; ++i) {
    printf(i == size-1 ? "%d\n" : "%d ", GetStart(comb)[i]);
  }

  for (size_t i = 0; i != rows; ++i) {
    for (size_t j = 0; j != GetRowLength(comb, i); ++j) {
      printf(j == GetRowLength(comb, i)-1 ? "%d\n" : "%d ",
             *GetElement(comb, i, j));
    }
  }

free:
  FreeComb(comb);
  return 0;
}
