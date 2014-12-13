#include "../common.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void print_proof(int* array, size_t array_length) {
    printf("%d %d %d\n", array[0], array[array_length / 2], array[array_length - 1]);
}

static void red1(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        return;
    }

    while (true) {
        bool swapped = false;
        for (size_t i = 0; i + 1 < array_length; i++) {
            if (array[i] > array[i + 1]) {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    if (run_mode == RM_LAST_ITERATION) {
        print_proof(array, array_length);
    }
}

static void green1(int* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        return;
    }

    qsort(array, array_length, sizeof(int), cmp_ints);
    if (run_mode == RM_LAST_ITERATION) {
        print_proof(array, array_length);
    }
}

BENCH(1, 50000, red1, green1)
