#include <assert.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>

// clang_opts: -lm

int put_complex(double complex number) {
  return printf("%.1f%+.1fi\n", creal(number), cimag(number));
}

int main(void) {
  float complex i = I;
  double _Complex another_i = i;

  put_complex(i);
  put_complex(another_i + 5.);
  put_complex(i * another_i);
  put_complex(cpow(I, CMPLX(6., 0.)));
  put_complex(csqrt(i));
}
