/*
   Exercise 5-2

   Write getfloat, the floating-point analog of
   getint. What type does getfloat return as its
   function value?

   NOTE: getfloat will still return an int. Since
   it is an analogue of getint, it will return EOF
   when there is no more input, or c (a char), it
   will still return an int. The main difference
   between the two will be the need to handle a
   decimal point, similar to how signs are handled,
   and using a pointer to a float rather than
   an int.
*/

#include <ctype.h>
#include <stdio.h>

#define SIZE 1000

int getfloat(float *);

int main(void) {
  float array[SIZE];
  int n;

  for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
    printf("Float = %g\n", array[n]);
}

int getch();
void ungetch(int c);

int getfloat(float *pn) {
  int c, sign;

  while (isspace(c = getch()))
    ;

  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    int next = getch();
    if (!isdigit(next)) {
      ungetch(c);
      return next;
    }

    c = next;
  }

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  if (c == '.') {
    c = getch();
    if (!isdigit(c))
      ungetch(c);

    int point;
    float dec;
    point = 0;
    for (dec = 0; isdigit(c); c = getch()) {
      dec = 10 * dec + (c - '0');
      point++;
    }

    if (point > 0)
      *pn += dec / (10 * point);
  }

  *pn *= sign;

  if (c != EOF)
    ungetch(c);

  return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
