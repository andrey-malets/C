#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int acquire_resource() {
  return open(__FILE__, O_RDONLY);
}

void release_resource(int fd) {
  close(fd);
}

int valid(int fd) {
  return fd != -1;
}

int process(int resource) {
  // TODO: get some processing done
  return 1;
}

void report_error() {
  fprintf(stderr, "error: %s\n", strerror(errno));
}

int main(void) {
  int rv = 0;
  int resource = acquire_resource();

  if (!valid(resource)) {
    goto err;
  }

  if (!process(resource)) {
    goto err;
  }

  if (0) {
  err:
    report_error();
    rv = 1;
  }

  release_resource(resource);
  return rv;
}
