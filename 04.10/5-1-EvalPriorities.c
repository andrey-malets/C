int main(void) {
  int x = 10;
  int y = 20;
  int z = 30;
  return x <= y || x + y == 30 && z < 50 ? 0 : z - y + z*3;
}
