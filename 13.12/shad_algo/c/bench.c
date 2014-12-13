#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 32 * 1024

void multiply(short* x, short* y, short* z) {
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        z[i] = x[i] * y[i];
    }
}

int main() {
    short* x = malloc(ARRAY_SIZE * sizeof(short));
    short* y = malloc(ARRAY_SIZE * sizeof(short));
    short* z = malloc(ARRAY_SIZE * sizeof(short));

    if (!x || !y || !z) {
        abort();
    }

    srand(42);

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        x[i] = rand();
        y[i] = rand();
    }

    for (size_t iter = 0; iter < 100000; iter++) {
        multiply(x, y, z);
    }

    printf("%d\n", z[ARRAY_SIZE / 2]);
}
