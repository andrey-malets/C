#include <stdio.h>

int main(void) {
  const char str[] = "a string";
  const char *str2 = "also a string";

  const char notstr[] = {'n','o','t',' ','a',' ','s','t','r','i','n','g'};
  const char wierd_str[] = {'m','a','y','b','e','\0'};

  printf("%s\n", str);
  printf("%s\n", str2);
  printf("%s\n", notstr);
  printf("%s\n", wierd_str);

  printf("%zu %zu %zu %zu\n",
         sizeof(str),
         sizeof(str2),
         sizeof(notstr),
         sizeof(wierd_str));

  return 0;
}
