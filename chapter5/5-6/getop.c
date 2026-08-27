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
 * This file only implements getop. Check the
 * other files in this folder for the other
 * functions.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char *);
void push(double);
double pop(void);

int main(void) {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("Divide by zero");
    case '\n':
      printf("%.8g\n", pop());
      break;
    default:
      printf("Unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("Stack full, cannot push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("Stack is empty\n");
    return 0;
  }
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char *s) {
  int c;
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;

  *(s + 1) = '\0';
  if (!isdigit(c) && c != '.')
    return c;
  if (isdigit(c))
      while (isdigit(*s++ = c = getch()))
        ;

  if (c == '.')
    while (isdigit(*s++ = c = getch()))
        ;

  *s = '\0';

  if (c != EOF)
    ungetch(c);

  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("Ungetch: too many characters\n");
  else
   buf[bufp++] = c;
}
