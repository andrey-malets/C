#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <thread>
#include <vector>

void init_single(char* mem, size_t size, char byte) {
  memset(mem, byte, size);
}

void init_multiple(char* mem, size_t size, char byte,
                   size_t num_threads) {
  assert(size % num_threads == 0);

  std::vector<std::thread> threads;
  const size_t stride = size/num_threads;

  for (size_t i = 0; i != num_threads; ++i)
    threads.push_back(std::thread(
        std::bind(memset, mem+(stride)*i, byte, stride)));

  for (std::thread& thread: threads)
    thread.join();
}

void check(char* mem, size_t size, char byte) {
  assert(mem[0] == byte);
  assert(mem[size-1] == byte);
}

int main(void) {
  const size_t size = 33L*1024*1024*1024;
  char* mem = (char*) malloc(size);

  // init_single(mem, size, 10);
  init_multiple(mem, size, 10, 11);

  // init_multiple(mem, size, 10, 12);
  // init_multiple(mem, size, 10, 12);
  // init_multiple(mem, size, 10, 12);
  // init_multiple(mem, size, 10, 12);

  check(mem, size, 10);

  free(mem);
}
