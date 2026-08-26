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
 * This file only implements atoi. Check the
 * other files in this folder for the other
 * functions.
 *
 * To not interfere with the standard library,
 * the function will be renamed to 'stoi'
 */
#include <stdio.h>

int stoi(char *string);

int main(void) {
  char *s = "23";

  printf("%d\n", stoi(s));
}

int stoi(char *s) {
  int n = 0;

  for (; *s >= '0' && *s <= '9'; s++) {
    n = 10 * n + (*s - '0');
    printf("n = %d, s* = %c\n", n, *s);
  }

  return n;
}
