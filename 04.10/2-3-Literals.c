int main(void) {
  int decimal = 10;
  int octal   = 012;
  int hex     = 0x0a;

  // int strange = 'ABC';

  return decimal == octal == hex;
}
