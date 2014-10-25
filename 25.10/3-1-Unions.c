#include <assert.h>
#include <math.h>

struct Point {
  union {
    struct {
      float x;
      float y;
    } cart;

    struct {
      float r;
      float phi;
    } pol;

  } value;

  enum Type {
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
      .value.cart = {
          p.value.pol.r * cos(p.value.pol.phi),
          p.value.pol.r * sin(p.value.pol.phi)
      }
    };
  default:
    assert(0);
    break;
  }
}

float cart_distance(struct Point p1, struct Point p2) {
  assert(p1.type == P_CARTESIAN && p2.type == P_CARTESIAN);
  float d1 = p1.value.cart.x - p2.value.cart.x;
  float d2 = p1.value.cart.y - p2.value.cart.y;
  return sqrt(d1*d1 + d2*d2);
}

int main(void) {
  struct Point p1 = { .value.cart = {1.0, 1.0},     .type = P_CARTESIAN };
  struct Point p2 = { .value.pol  = {1.41, M_PI/4}, .type = P_POLAR };
  return fabs(cart_distance(to_cartesian(p1), to_cartesian(p2))) > 0.01;
}
