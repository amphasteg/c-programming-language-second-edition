/*
  Exercise 1-10
  Write a program to cpoy its input to its output,
  replacing each tab by \t, each backspace by \b,
  and each backslash by \\. This makes tabs and backspaces
  visible in an unambiguos way.

  Note: There is no way to do this without an if else statement, 
  so that is what I did.
*/

#include <stdio.h>

int main()
{
  int c;

  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
      printf("\\t");
    else if (c == '\b')
      printf("\\b");
    else
      putchar(c);
  }
}
