#include <stdio.h>

int main(void) {
  char _10_chars_is_enough_for_everyone[10];

  gets(_10_chars_is_enough_for_everyone);

  // fgets(_10_chars_is_enough_for_everyone,
  //       sizeof(_10_chars_is_enough_for_everyone),
  //       stdin);

  puts(_10_chars_is_enough_for_everyone);
}
