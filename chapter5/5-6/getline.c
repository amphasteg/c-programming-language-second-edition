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
 * This file only implements getline. Check the
 * other files in this folder for the other 
 * functions.
*/

#include <stdio.h>

#define LEN 1000

int getline(char* line, int max);

int main(void) {
  int len;
  char line[LEN];

  len = getline(line, LEN);

  printf("Line: %s\nlen %d\n", line, len);
}

int getline(char* line, int max) {
  int c, i;

  for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *(line + i) = c;

  if (c == '\n') {
    *(line + i) = c;
    i++;
  }

  *(line + i) = '\0';

  return i;
}


