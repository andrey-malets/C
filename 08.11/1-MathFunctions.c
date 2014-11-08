#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>

// clang_opts: -lm

int check(double expected, double actual, double threshold) {
  if (isnan(expected)) {
    return isnan(actual);
  } else if (isinf(expected)) {
    return isinf(actual);
  } else {
    return fabs((expected - actual) / actual) < threshold;
  }
}

void assert_eq(double expected, double actual, double threshold) {
  if (!check(expected, actual, threshold)) {
    fprintf(stderr, "expected:  %lf\n", expected);
    fprintf(stderr, "actual:    %lf\n", actual);
    fprintf(stderr, "threshold: %lf\n", threshold);
#define DOUBLE_VALUES_ARE_EQUAL 0
    assert(DOUBLE_VALUES_ARE_EQUAL);
#undef DOUBLE_VALUES_ARE_EQUAL
  }
}

int main(void) {
  assert_eq(3.1415, M_PI, 1e-3);
  assert_eq(1., sin(M_PI/2), 1e-5);
  assert_eq(-M_PI/2, asin(-1.), 1e-10);

  assert_eq(NAN, sqrt(-1), 0);
  assert_eq(NAN, asin(10.), 0);

  assert_eq(NAN, 0./0., 0);
  assert_eq(INFINITY, 1./0., 0);
}
