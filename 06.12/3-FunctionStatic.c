int f(int x) {
  static int y = 10;
  return x + y;
}

int main(void) {
  return f(10);
}
