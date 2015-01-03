#include "table.h"

#include <assert.h>
#include <string.h>


struct Elem {
  struct Elem *next;
  char data[];
};

struct HashTable {
  struct HashTableParams params;
  size_t size;
  struct Elem *buckets[];
};


struct HashTable *allocate_table(size_t size, struct HashTableParams params) {
  assert(params.hash);
  assert(params.elem_size);

  size_t buckets_size = size * sizeof(struct Elem *);
  struct HashTable *rv = malloc(sizeof(struct HashTable) + buckets_size);

  if (rv) {
    rv->params = params;
    rv->size = size;
    memset(rv->buckets, buckets_size, 0);
  }

  return rv;
}

void deallocate_table(struct HashTable *table) {
  if (table) {
    for (size_t i = 0; i != table->size; ++i) {
      for (struct Elem *bucket = table->buckets[i]; bucket;) {
        struct Elem *victim = bucket;
        bucket = bucket->next;
        free(victim);
      }
    }
    free(table);
  }
}

static int matches(struct HashTableParams *params, void *target,
                   size_t hash, struct Elem *elem) {
  if (params->hash(params->hash_ctx, elem->data) == hash)
    return params->equal ?
        params->equal(target, elem->data) :
        memcmp(target, elem->data, params->elem_size) == 0;
  return 0;
}

static struct Elem **find_matching(struct HashTable *table, void *target) {
  size_t hash = table->params.hash(table->params.hash_ctx, target);
  size_t bucket = hash % table->size;

  struct Elem **pelem = &table->buckets[bucket];
  while (*pelem && !matches(&table->params, target, hash, *pelem))
    pelem = &(*pelem)->next;
  return pelem;
}

int table_has(struct HashTable *table, void *target) {
  return *find_matching(table, target) != 0;
}

int table_insert(struct HashTable *table, void *target) {
  struct Elem **pelem = find_matching(table, target);
  if (*pelem) {
    memcpy((*pelem)->data, target, table->params.elem_size);
    return 1;
  } else {
    *pelem = malloc(sizeof(struct Elem) + table->params.elem_size);
    if (!*pelem) {
      return -1;
    } else {
      (*pelem)->next = 0;
      memcpy((*pelem)->data, target, table->params.elem_size);
      return 0;
    }
  }
}

int table_remove(struct HashTable *table, void *target) {
  struct Elem **pelem = find_matching(table, target);
  if (!*pelem)
    return 0;

  struct Elem *victim = *pelem;
  *pelem = (*pelem)->next;
  free(victim);
  return 1;
}
