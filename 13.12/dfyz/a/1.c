#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {
    size_t array_length = atoll(argv[1]);
    int* array = malloc(array_length * sizeof(int));
    if (!array) {
        abort();
    }

    const size_t steps = 64 * 1024 * 1024;
    clock_t start = clock();
    const size_t length_mod = array_length - 1;
    for (size_t i = 0; i < steps; i++) {
        array[(i * 16) & length_mod]++;
    }
    clock_t end = clock();
    printf("%.3f (array length = %zu)\n", (double)(end - start) / CLOCKS_PER_SEC, array_length);
}

