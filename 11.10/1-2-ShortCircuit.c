int main(void) {
  int x = 0, y = 1;
  int *px = &x, *py = &y - 100;

  if (*px == 0 || *py < 100) {
    return 0;
  }
  return 1;
}
