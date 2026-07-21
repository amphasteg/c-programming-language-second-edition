/*
   Exercise 1-20
   Write a program `detab` that replaces tabs in the input with the proper number
   of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
   Should n be a variable or a symbolic parameter?
 */
#include <stdio.h>

#define TAB_SPACES 8

int main()
{
  int c, count;
  
  count = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      count = 0;
      putchar(c);
    }
    else if (c == '\t') {
      int spaces = TAB_SPACES - (count % TAB_SPACES);
      for (int i = 0; i < spaces; i++)
        putchar(' ');
    }
    else {
      count++;
      putchar(c);
    }
  }
}

