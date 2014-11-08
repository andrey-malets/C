#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Student {
  const char *name;
  unsigned score;
  unsigned last_submission;
};

#define VOID_PREFIX voidfn
#define DEFINE_VOID(name, type) \
int VOID_PREFIX ## name(const void* lhs, const void* rhs) {\
  return name((type *)lhs, (type *)rhs);\
}
#define USE_VOID(name) VOID_PREFIX ## name

int compare_by_name(const struct Student *left,
                    const struct Student *right) {
  return strcmp(left->name, right->name);
}
DEFINE_VOID(compare_by_name, struct Student)

int compare(unsigned lhs, unsigned rhs) {
  return (lhs > rhs) ? -1 : (lhs < rhs);
}

int compare_by_score(const struct Student *left,
                     const struct Student *right) {
  int rv = compare(left->score, right->score);
  rv = rv ? rv : -compare(left->last_submission, right->last_submission);
  return rv;
}
DEFINE_VOID(compare_by_score, struct Student)

int put_score(const struct Student *student) {
  return printf("%.20s had %u at %u\n",
                student->name,
                student->score,
                student->last_submission);
}

int main(int argc, char *argv[]) {
  struct Student shad14[] = {
    {"Anton Fedorov",   6, 2},
    {"Darya Svalova",   5, 3},
    {"Nikita Dmitriev", 5, 5},
    {"Pavel Gein",      5, 1},
    {"Victor Samun",    6, 4}
  };

  size_t size = sizeof(struct Student);
  size_t n = sizeof(shad14)/size;

  struct Student to_find = {"Pavel Gein", 0, 0};
  // struct Student to_find = {"Vassily Poupkine", 0, 0};
  struct Student *found = bsearch(&to_find, shad14, n, size,
                                  USE_VOID(compare_by_name));
  if (found) {
    put_score(found);
  } else {
    puts("not found");
  }
  puts("");

  qsort(shad14, n, size, USE_VOID(compare_by_score));
  for (size_t i = 0; i != n; ++i) {
    put_score(&shad14[i]);
  }
}
