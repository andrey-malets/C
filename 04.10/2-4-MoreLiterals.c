int main(void) {
  char letter      = 'T';
  char also_letter = 65;
  char *string     = "This \\"
                     "is a valid\
                     string!\n";
  puts(string);
  return letter - string[0];
}
