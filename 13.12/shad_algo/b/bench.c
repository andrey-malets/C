#include "../common.h"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

static void sum_elements(int* array, size_t array_length, RunMode run_mode) {
    long long sum = 0;
    for (size_t i = 0; i < array_length; i++) {
        if (array[i] >= RAND_MAX / 2) {
            sum += array[i];
        }
    }
    if (run_mode == RM_LAST_ITERATION) {
        printf("%lld\n", sum);
    }
}

static void red2(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        qsort(array, array_length, sizeof(int), cmp_ints);
        return;
    }

    sum_elements(array, array_length, run_mode);
}

static void green2(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        return;
    }

    sum_elements(array, array_length, run_mode);
}

BENCH(10000, 32768, red2, green2)
