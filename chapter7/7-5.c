/*
 * Exercise 7-5
 *
 * Rewrite the postfix calculator of Chapter 4 to
 * use scanf and/or sscanf to do the input and
 * number conversion.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP                                    \
  100 /* max size of operand or operator */
#define CONSUMED                                 \
  1 /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  int num;
  char c;

  while ((type = scanf("%d", &num)) != EOF) {
    if (type == CONSUMED)
      push(num);
    else if ((type =
                  scanf(" \t%c", &c) == CONSUMED))
      switch (c) {
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
      // Instead of using \n here, we use 'E', as
      // scanf("%d") skips all whitespace
      case 'E':
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %c\n", c);
        break;
      }
  }
  return 0;
}

#define MAXVAL                                   \
  100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n",
           f);
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
