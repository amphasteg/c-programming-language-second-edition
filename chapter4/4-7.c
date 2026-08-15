/*
   Exercise 4-7

   Write a routine ungets(s) that will push back
   an entire string onto the input. Should ungets
   know about buf and bufp, or should it just use
   ungetch?
*/

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define VARSET '='
#define VARGET 'a'
#define MAX_VARS 26

int getop(char[]);
void push(double);
double pop(void);
void peek(void);
void duplicate(void);
void swap(void);
void clear(void);
void ungets(char[]);

char var = '\0';

/* reverse Polish calculator */
int main(void) {
  int type, index;
  double op2;
  char s[MAXOP];
  double vars[MAX_VARS] = {0};

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
    case '^':
      push(pow(pop(), pop()));
      break;
    case 'X':
      push(exp(pop()));
      break;
    case '~':
      push(sin(pop()));
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
    case 'P':
      peek();
      break;
    case 'D':
      duplicate();
      break;
    case 'S':
      swap();
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    case VARGET:
      index = var - 'a';
      printf("Pushing varibale %g from var %c (index %d)\n", vars[index], index,
             index);
      if (vars[index] != 0)
        push(vars[index]);
      else {
        push(0);
        printf("Variable %c returned as 0\n", var);
      }
      break;
    case VARSET:
      if (getop(s) == VARGET) {
        int index = var - 'a';
        vars[index] = pop();
        printf("Assigning value of %g to variable %c\n (index %d)\n", vars[index],
               var, index);
      } else
        printf(
            "Invalid assignment: \'=\' needs to be followed by \'a\'-\'z\'\n");
      break;

    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

void peek(void) {
  if (sp > 0)
    printf("The value on the top of the stack is %g\n", val[sp - 1]);
  else
    printf("There is nothing to peek at. The stack is empty\n");
}

void duplicate(void) {
  double temp = pop();

  push(temp);
  push(temp);

  printf("Duplicated %g on the stack\n", temp);
}

void swap(void) {
  double top = pop();
  double second = pop();

  push(top);
  push(second);

  printf("Swapped %g to be on top of the stack, and %g to be below it\n",
         second, top);
}

void clear(void) {
  for (int i = 0; i <= sp; i++)
    val[i] = 0.0;
  sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[]) {
  int i, c;
  i = 0;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (c >= 'a' && c <= 'z') {
    var = c;
    int next = getch();
    // Discard next if \n to avoid popping on empty stack
    if (next != '\n')
      ungetch(next);
    return VARGET;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '=')
    return c; /* not a number */
  if (c == '=')
    return VARSET;

  if (c == '-') {
    int next = getch();
    if (next == ' ' || next == '\t' || next == '\n') {
      ungetch(next);
      return c; // return op
    } else if (!isdigit(next) && next != '.')
      return next; // not a number
    else
      s[++i] = c = next;
  }

  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}


#define BUFSIZE 100

int length(char[]);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed-back) character */
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void ungets(char s[]) {
  if (length(s) + bufp > BUFSIZE) {
    printf("Ungets: too many characters");
    return;
  }

  for (int i = 0; s[i] != '\0'; i++)
    buf[bufp++] = s[i];
}

int length(char s[]) {
  int i = 0;
  while (i < BUFSIZE && s[i] != '\0')
    i++;
  return i;
}
