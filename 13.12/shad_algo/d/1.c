#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int main() {
    double x = nextafter(0.0, 1.0);
    printf("%.16g\n", x);

    double y = nextafter(x, 1.0);
    printf("%.16g\n", y);

    double z = DBL_MIN;
    printf("%.16g\n", z);

    double t = nextafter(z, 1.0);
    printf("%.16g\n", t);
}

