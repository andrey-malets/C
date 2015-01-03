#include "table.h"

#include <assert.h>

size_t hash_func(void *ctx, void *ptr) {
  int *value = ptr;
  int *prime = ctx;
  return *value % *prime;
}

void test_hash(int prime, int table_size, int elems_count) {
  struct HashTableParams params = GET_HASH_PARAMS(&prime, hash_func, 0, int);
  struct HashTable *table = allocate_table(table_size, params);
  for (int i = 0; i != elems_count; ++i) {
    for (int j = 0; j != i; ++j) {
      int value = j * j;
      assert(table_has(table, &value));
      assert(table_insert(table, &value) == 1);
    }

    for (int j = i; j != elems_count; ++j) {
      int value = j * j;
      assert(!table_has(table, &value));
      assert(!table_remove(table, &value));
    }

    int value = i * i;
    assert(!table_insert(table, &value));
  }

  for (int i = 0; i != elems_count; ++i) {
    for (int j = i; j != elems_count; ++j) {
      int value = j * j;
      assert(table_has(table, &value));
    }

    int value = i * i;
    assert(table_remove(table, &value));
    assert(!table_remove(table, &value));

    for (int j = 0; j != i; ++j) {
      int value = j * j;
      assert(!table_has(table, &value));
    }
  }

  deallocate_table(table);
}

int main(void) {
  test_hash(10007, 191, 1000);
}
