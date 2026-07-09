/*
  Exercise 1-9
  Write a program to copy its input to its output,
  replacing each string of one or more blanks by a single blank

  Note: Since this exercise is before 1.5.4, 
  this solution does not inlcude else statements or the OR (||) operator,
  hence, this program is not *technically* the best solution 
  to this problem. After reading 1.5.4, it try optimizing this!
*/

#include <stdio.h>

int main()
{
  int blank, c;

  blank = 0;

  while ((c = getchar()) != EOF)
  {
    if (c == ' ')
      blank++;

    if (c != ' ')
      blank = 0;

    if (blank <= 1)
      putchar(c);
  }
}
