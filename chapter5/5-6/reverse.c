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
 * This file only implements reverse. Check the
 * other files in this folder for the other 
 * functions.
*/
#include <string.h>
#include <stdio.h>

void reverse(char* s);

int main(void) {
  char* s = "String";

  printf("%s\n", s);

  reverse(s);
  printf("%s\n", s);
}

void reverse(char* s) {
  int c;

  char* t = s + strlen(s) - 1;

  for ( ; s < t; s++, t--) {
    c = *s;
    *s = *t;
    *t = c;
  }
}
