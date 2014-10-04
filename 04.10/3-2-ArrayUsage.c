int main(void) {
  int x[] = {1,2,3,4,5};
  x[1] = 10;
  return x[x[0]] + x[3];
}
