int main(void) {
  int x[] = {1, 2, 3};
  int y[] = {4, 5, 6};

  int *px;

  px = &x[0];
  px = &y[2];

  // y = &x[0];

  return *px;
}
