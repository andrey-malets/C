#define _GNU_SOURCE
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <numa.h>

#define CORE_COUNT 32

void pin_to_core(size_t core) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
}

void bench(size_t core, char* array, size_t array_size) {
    pin_to_core(core);
    clock_t start = clock();

    for (size_t i = 0; i < array_size; i++) {
        *(array + ((i * 1009) % array_size)) += 1;
    }

    clock_t end = clock();
    printf("Core %zu, time: %.3f\n", core, (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    const size_t array_size = 100 * 1000 * 1000;

    pin_to_core(0);
    char* array = numa_alloc_local(array_size);
    if (!array) {
        abort();
    }

    for (size_t core = 0; core < CORE_COUNT; core++) {
        bench(core, array, array_size);
    }
}
