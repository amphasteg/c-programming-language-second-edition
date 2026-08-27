/*
 * Exercise 5-6
 * Rewrite appropriate programs from earlier
 * chapters and exercises with pointers instead
 * of array indexing. Good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and
 * their variants (Chapters 2, 3, and 4), reverse
 * (Chapter 3), and strindex, and getop
 * (Chapter 4).
 *
 * This file only implements strindex. Check the
 * other files in this folder for the other
 * functions.
 */

#include <stdio.h>

#define LEN 1000

int strindex(char *src, char *searchfor);

int main() {
  char *string = "This is a string";
  char *search = "is";

  printf("%d\n", strindex(string, search));
}

int strindex(char *source, char *searchfor) {
  int i, j;
  for (i = 0; *(source + i); i++) {
    for (j = 0; *(searchfor + j) != '\0' && *(source + i) == *(searchfor + j);
         j++)
      ;
    if (j > 0 && *(searchfor + j))
      return i;
  }
  return -1;
}
