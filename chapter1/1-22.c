/*
   Exercise 1-22
   Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character
   that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines,
   and if there are no blanks or tabs befored the specified column.
*/
#include <stdio.h>

#define CUTOFF 12
#define MIN 8

int main() {
  int count, c;

  count = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
      count = 0;
    }
    else if (MIN < count && (c == ' ' || c == '\t')) {
      putchar('\n');
      count = 0;
    }
    else if (count > CUTOFF)
    {
      putchar('-');
      putchar('\n');
      putchar(c);
      count = 0;
    }
    else {
      putchar(c);
    }
    count++;
  }
}
