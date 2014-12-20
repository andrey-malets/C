#pragma once

#include <cstdint>

struct TNumber {
	static const uint64_t MOD = 1000000007;

	uint64_t X;

	TNumber(uint64_t x)
		: X(x)
	{}

	TNumber operator+(const TNumber& other) const {
		return (X + other.X) % MOD;
	}

	TNumber operator-(const TNumber& other) const {
		return (X - other.X) % MOD;
	}

	TNumber operator*(const TNumber& other) const {
		return (X * other.X) % MOD;
	}

	TNumber operator/(const TNumber& other) const {
		return (*this) * other.Inverse();
	}

	TNumber Inverse() const {
		uint64_t p = MOD - 2;
		TNumber result = 1;
		TNumber x = *this;
		while (p) {
			if (p % 2 == 1) {
				result = result * x;
			}
			p /= 2;
			x = x * x;
		}
		return result;
	}
};
