#include "../common.h"

#include <stdlib.h>
#include <stdio.h>

static void sum_elements(int* array, size_t array_length, RunMode run_mode) {
    long long sum = 0;
    for (size_t i = 0; i < array_length; i++) {
        sum += array[array[i]];
    }
    if (run_mode == RM_LAST_ITERATION) {
        printf("%lld\n", sum);
    }
}

static void fill_indexes(int* array, size_t array_length) {
    for (size_t i = 0; i < array_length; i++) {
        array[i] = i;
    }
}

static void random_shuffle(int* array, size_t array_length) {
    for (size_t i = array_length; i > 0; i--) {
        size_t j = rand() % i;
        int tmp = array[i - 1];
        array[i - 1] = array[j];
        array[j] = tmp;
    }
}

static void red2(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        fill_indexes(array, array_length);
        return;
    }

    sum_elements(array, array_length, run_mode);
}

static void green2(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        fill_indexes(array, array_length);
        random_shuffle(array, array_length);
        return;
    }

    sum_elements(array, array_length, run_mode);
}

BENCH(1, 100000000, red2, green2)
