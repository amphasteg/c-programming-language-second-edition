/*
   Exercise 4-3

   Given the basic framework, it's straightforward
   to extend the calculator. Add the modulus (%)
   operator and provisions for negative numbers.

   Test
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop();
int getch(void);
void ungetch(int c);

// Reverse polish calculator
int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
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
        printf("Error: Divide by Zero\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push((int)pop() % (int)op2);
      else
        printf("Error: Modulus by Zero");
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("Unknown command: %c", type);
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
    printf("Error: stack is full, cannot push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("Error: stack is empty");
    return 0.0;
  }
}

int getop(char s[]) {
  int i = 0;
  int c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;

  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-') {
    return c;
  }

  if (c == '-') {
    int next = getch();
    if (next == '\n' || next == ' ' || next == '\t') {
      ungetch(next);
      return c; // return '-' as operator
    } else if (!isdigit(next) && next != '.') {
      return next; // not a number
    } else         // number like "-5", "-.6" etc, next is digit or '.'
    {
      s[++i] = c = next;
    }
  } else {
    c = getch();
  }

  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  if (c != EOF) {
    ungetch(c);
  }

  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buf[bufp--] : getchar(); }

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("Ungetch: too many characters");
  else
    buf[bufp++] = c;
}
