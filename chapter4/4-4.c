/*
   Exercise 4-4

   Add the commands to print the top elements of
   the stack without popping, to duplicate it,
   and to swap the top two elements. Add a
   command to clear the stack.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);
void peek(void);
void duplicate(void);
void swap(void);
void clear(void);

/* reverse Polish calculator */
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
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
       printf("Error: zero modulo");
      break;
    case 'p':
      peek();
      break;
    case 'd':
      duplicate();
      break;
    case 's':
      swap();
      break;
    case '\n':
      printf("\t%.8g\n", pop());
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
    printf("The value on the top of the stack is %g\n", val[sp-1]);
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

  printf("Swapped %g to be on top of the stack, and %g to be below it\n", second, top);
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
  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */
  if (c == '-') {
    int next = getch();
    if (next == ' ' || next == '\t' || next == '\n') {
      ungetch(next);
      return c; //return op
    }
    else if (!isdigit(next) && next != '.')
      return next; //not a number
    else
     s[++i] = c = next;
  }
  else
    c = getch();

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
