#define ELEM_TYPE float
#include "../common.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FLOAT_COUNT 16

const float a[] = {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6};
const float b[] = {1.123,1.234,1.345,156.467,1.578,1.689,1.790,1.812,1.923,2.034,2.145,2.256,2.367,2.478,2.589,2.690};

static void prepare_floats(float* array) {
    memcpy(array, a, sizeof(float) * FLOAT_COUNT);
}

static void crunch_floats(float delta, float* array) {
    for(size_t i = 0; i < FLOAT_COUNT; i++)
    {
        array[i] *= a[i];
        array[i] /= b[i];
        array[i] += delta;
        array[i] -= delta;
    }
}

static void print_floats(float* array) {
    for (size_t i = 0; i < FLOAT_COUNT; i++) {
        printf("%g\n", array[i]);
    }
}

static void red3(float* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        prepare_floats(array);
        return;
    }

    crunch_floats(0.5f, array);

    if (run_mode == RM_LAST_ITERATION) {
        print_floats(array);
    }
}

static void green35(float* array, size_t array_length, RunMode run_mode) {
    if (run_mode == RM_PREPARE) {
        prepare_floats(array);
        return;
    }

    crunch_floats(0.0f, array);

    if (run_mode == RM_LAST_ITERATION) {
        print_floats(array);
    }
}

BENCH(2000000, FLOAT_COUNT, red3, green35)
