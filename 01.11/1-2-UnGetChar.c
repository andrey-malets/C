#include <stdio.h>
#include <assert.h>

int put_back(char c) {
  return ungetc(c, stdin);
}

int is_ws(char c) {
  switch (c) {
  case ' ':
  case '\t':
  case '\n':
    return 1;
  default:
    return 0;
  }
}

int try_parse(char fst, char snd) {
  int a = getchar(), b, c;
  if (a != fst) {
    put_back(a);
    return 0;
  }

  b = getchar(); assert(b == snd);

  do {
    c = getchar();
  } while (is_ws(c));

  if (!is_ws(c)) {
    ungetc(c, stdin);
  }
  return 1;
}

int try_parse_ab() {
  return try_parse('a', 'b');
}

int try_parse_cd() {
  return try_parse('c', 'd');
}

int main(void) {
  while (!feof(stdin)) {
    if (try_parse_ab()) {
      puts("got ab");
    } else if (try_parse_cd()) {
      puts("got cd");
    } else {
      return 1;
    }
  }
}
