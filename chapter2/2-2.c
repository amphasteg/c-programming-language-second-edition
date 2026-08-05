/*
   Exercise 2-2
   Write a loop equivalent to the for loop above without using && or ||
 */

#include <stdio.h>

int main() {
  int limit = 1000;
  char string[limit];

  for (int i = 0; i < limit-1; i++) {
    char c = getchar();
    
    if (c == '\n')
      i = limit;

    if (c == EOF)
      i = limit;

    string[i] = limit;
  }

  printf("%s", string);
}
