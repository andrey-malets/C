int mul(int x, int n) {
  return (n == 1) ? x : x + mul(x, n-1);
}

int main(void) {
  return mul(10, 20);
}
