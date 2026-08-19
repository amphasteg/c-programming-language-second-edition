/*
   Exercise 4-8

*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

int length(char[]);

int buf = -1;      /* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character */
{
  int val = buf;

  if (val == -1) {
    val = getchar();
    printf("There is nothing in the buffer");
  }
  else
    buf = -1;

  return val;
}

void ungetch(int c) /* push character back on input */
{
  buf = c;
}
