/*
   Exercise 2-10

   Rewrite the function lower, which converts
   upper case letters to lower case, with a 
   conditional expression instead of if-else.
*/

#include <stdio.h>

char lower(char c);

int main() {
  char string[4];

  string[0] = 't';
  string[1] = 'E';
  string[2] = 'S';
  string[3] = 'T';

  for (int i = 0; i < 4; i++)
    string[i] = lower(string[i]);

  printf("%s", string);
}

char lower(char c) {
  return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
