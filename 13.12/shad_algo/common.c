#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static void start_color(const char* color) {
    printf("%c[0;%sm", 27, color);
}

static void end_color() {
    printf("%c[0m", 27);
}

static void bench(size_t iter_count, size_t array_length, Runner runner, const char* color) {
    ELEM_TYPE* array = malloc(array_length * sizeof(ELEM_TYPE));
    if (!array) {
        fputs("Couldn't allocate an array\n", stderr);
        exit(EXIT_FAILURE);
    }

    puts("Running...");

    srand(0xCAFEBABE);
    for (size_t j = 0; j < array_length; j++) {
        array[j] = rand();
    }

    runner(array, array_length, RM_PREPARE);

    clock_t start = clock();
    for (size_t i = 0; i < iter_count; i++) {
        bool last_iteration = i + 1 == iter_count;
        runner(array, array_length, last_iteration ? RM_LAST_ITERATION : RM_REGULAR);
    }
    clock_t end = clock();

    start_color(color);
    printf("%.3fs\n", (double)(end - start) / CLOCKS_PER_SEC);
    end_color();
}

int cmp_ints(const void* a, const void* b) {
    int fst = *((const int*)a);
    int snd = *((const int*)b);
    if (fst < snd) {
        return -1;
    } else if (fst > snd) {
        return 1;
    }
    return 0;
}

void do_main(int argc, char* argv[], size_t iter_count, size_t array_length, Runner red, Runner green) {
    if (argc != 2) {
        fputs("Expected one argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    const char* arg = argv[1];
    if (strcmp(arg, "red") == 0) {
        bench(iter_count, array_length, red, "31");
    } else if (strcmp(arg, "green") == 0) {
        bench(iter_count, array_length, green, "32");
    } else {
        fputs("Expected 'red' or 'green'\n", stderr);
        exit(EXIT_FAILURE);
    }
}

