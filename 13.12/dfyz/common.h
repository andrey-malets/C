#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifndef ELEM_TYPE
#define ELEM_TYPE int
#endif

typedef enum {
    RM_PREPARE,
    RM_REGULAR,
    RM_LAST_ITERATION,
} RunMode;

typedef void (*Runner)(ELEM_TYPE* array, size_t array_length, RunMode run_mode);

int cmp_ints(const void* a, const void* b);

void do_main(int argc, char* argv[], size_t iter_count, size_t array_length, Runner red, Runner green);

#define BENCH(ITER_COUNT, ARRAY_SIZE, RED_RUNNER, GREEN_RUNNER) \
    int main(int argc, char* argv[]) { \
        do_main(argc, argv, ITER_COUNT, ARRAY_SIZE, RED_RUNNER, GREEN_RUNNER); \
    }
