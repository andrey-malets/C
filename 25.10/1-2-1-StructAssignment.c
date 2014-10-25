#include <stdlib.h>

#define simplearraysize(x) (sizeof(x)/sizeof(x[0]))

struct Point3D {
  int coord[3];
};

struct Point3D adjust_point(struct Point3D point) {
  for (size_t i = 0; i != simplearraysize(point.coord); ++i) {
    ++point.coord[i];
  }

  return point;
}

int main(void) {
  struct Point3D before = {{1, 2, 3}};
  struct Point3D after = adjust_point(before);

  return after.coord[2] - before.coord[2];
}
