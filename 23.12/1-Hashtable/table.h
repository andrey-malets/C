#pragma once

#include <stdlib.h>

struct HashTableParams {
  void *hash_ctx;
  size_t (*hash)(void *hash_ctx, void *value);

  int (*equal)(void *lhs, void *rhs);
  size_t elem_size;
};

#define GET_HASH_PARAMS(ctx, hash, equal, type) {\
  ctx, hash, equal, sizeof(type) }

struct HashTable;
struct HashTable *allocate_table(size_t size, struct HashTableParams params);
void deallocate_table(struct HashTable *table);

int table_has(struct HashTable *table, void *target);
int table_insert(struct HashTable *table, void *target);
int table_remove(struct HashTable *table, void *target);
