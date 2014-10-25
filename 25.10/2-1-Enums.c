enum First {
  F_ONE = 1,
  F_TEN = 10
};

enum Second {
  S_ZERO,
  S_ONE,
};

int main(void) {
  return F_ONE - S_ONE;
}
