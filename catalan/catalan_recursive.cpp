#include <iostream>

#include "number.h"

TNumber Catalan(TNumber x) {
	if (x.X == 0) {
		return 1;
	}
	return (x * 2 - 1) * 2 * Catalan(x - 1) / (x + 1);
}

int main() {
	uint64_t x;
	std::cin >> x;
	std::cout << Catalan(x).X << std::endl;
}
