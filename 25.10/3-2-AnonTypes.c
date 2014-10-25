#include <assert.h>
#include <math.h>

// clang_opts: -std=c11

struct Point {
  union {
    struct { float x; float y; };
    struct { float r; float phi; };
  };

  enum {
    P_CARTESIAN,
    P_POLAR
  } type;
};

struct Point to_cartesian(struct Point p) {
  switch (p.type) {
  case P_CARTESIAN:
    return p;
    break;
  case P_POLAR:
    return (struct Point) {
      .type = P_CARTESIAN,
      .x = p.r * cos(p.phi),
      .y = p.r * sin(p.phi)
    };
  default:
    assert(0);
    break;
  }
}

float cart_distance(struct Point p1, struct Point p2) {
  assert(p1.type == P_CARTESIAN && p2.type == P_CARTESIAN);
  float d1 = p1.x - p2.x;
  float d2 = p1.y - p2.y;
  return sqrt(d1*d1 + d2*d2);
}

int main(void) {
  struct Point p1 = { .x = 1.0,  .y = 1.0,      .type = P_CARTESIAN };
  struct Point p2 = { .r = 1.41, .phi = M_PI/4, .type = P_POLAR };
  return fabs(cart_distance(to_cartesian(p1), to_cartesian(p2))) > 0.01;
}
