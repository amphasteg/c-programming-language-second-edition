/*
 * Exercise 5-10
 *
 * Write the program expr, which evaluates a
 * reverse Polish expression from the command
 * line, where each operator or operand is a
 * separate argument. For example, expr 2 3 4 + *
 * evaluates 2 * (3+4).
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char *, char *);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
  int type;
  double op2;
  char s[MAXOP];

  while (--argc > 0) {
    ++argv;
    type = getop(s, *argv);
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
          printf("error: zero divisor\n");
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0)
          push((int)pop() % (int)op2);
        else
          printf("Error: zero modulo");
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
      argc--;
    }
  }

  printf("\t%.8g\n", pop());
  return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, cannot push %g\n", f);
}

double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

#include <ctype.h>

int getop(char *s, char* arg) {
  int c;

  while ((*s = c = *arg++) == ' ' || c == '\t')
    ;

  *(s + 1) = '\0';

  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  if (c == '-') {
    int next = *arg++; 
    if (next == ' ' || next == '\t' || next == '\n' || !next) {
      return c;
    } else if (!isdigit(next) && next != '.')
      return next;
    else
      *(++s) = c = next;
  }

  if (isdigit(c))
    while (isdigit(*(++s) = c = *arg++)) 
      ;

  if (c == '.')
    while (isdigit(*(++s) = c = *arg))
      ;

  *s = '\0';
  return NUMBER;
}
