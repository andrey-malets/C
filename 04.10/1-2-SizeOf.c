int main(void) {
  // char      really_small_value;
  // short     small_value;
  // int       ordinary_value;
  // long      not_so_long_value;
  // long long maybe_longer_value;

  // float  simple_real;
  // double little_less_simple_real;

  // return sizeof(not_so_long_value) < sizeof(maybe_longer_value);
  // return sizeof(ordinary_value) < sizeof(maybe_longer_value);

  return          1 <= sizeof(char) &&
      sizeof(char)  <  sizeof(short) &&
      sizeof(short) <= sizeof(int) &&
      sizeof(int)   <= sizeof(long) &&
      sizeof(long)  <= sizeof(long long);
}
