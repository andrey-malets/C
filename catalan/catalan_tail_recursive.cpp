#include <iostream>

#include "number.h"

TNumber Catalan(TNumber x, TNumber& numerator, TNumber& denominator) {
	if (x.X == 0) {
		return numerator / denominator;
	}
	numerator = numerator * (x * 2 - 1) * 2;
	denominator = denominator * (x + 1);
	return Catalan(x - 1, numerator, denominator);
}

int main() {
	uint64_t x;
	std::cin >> x;
	TNumber numerator(1);
	TNumber denominator(1);
	std::cout << Catalan(x, numerator, denominator).X << std::endl;
}
