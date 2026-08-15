/*
   Exercise 4-10

   
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
#define MAX_LINE 1000

int getop(char[]);
void push(double);
double pop(void);
void peek(void);
void duplicate(void);
void swap(void);
void clear(void);
int get_line(char[], int max);

char line[MAX_LINE];
int line_index = 0;
char var = '\0';

/* reverse Polish calculator */
int main(void) {
  int type, index;
  double op2;
  char s[MAXOP];
  double vars[MAX_VARS] = {0};

  while (get_line(line, MAX_LINE) != 0) {
    line_index = 0;
    while ((type = getop(s)) != EOF && type != '\0') {
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
        printf("Pushing varibale %g from var %c (index %d)\n", vars[index],
               index, index);
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
          printf("Assigning value of %g to variable %c\n (index %d)\n",
                 vars[index], var, index);
        } else
          printf("Invalid assignment: \'=\' needs to be followed by "
                 "\'a\'-\'z\'\n");
        break;

      default:
        //printf("error: unknown command %s\n", s);
        break;
      }
    }
  }
  return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL) {
    //printf("Pushed %g to stack. Stack is %d", f, sp);
    val[sp++] = f;
  }
  //else
    //printf("error: stack full, can't push %g\n", f);
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

/* getop: get next character or numeric operand */
int getop(char s[]) {
  int i, c;
  i = 0;

  while ((s[0] = c = line[line_index++]) == ' ' || c == '\t')
    ;
  if (c >= 'a' && c <= 'z') {
    var = c;
    int next = line[line_index++];
    // Discard next if \n to avoid popping on empty stack
    if (next != '\n')
      line_index--;
    return VARGET;
  }

  if (!isdigit(c) && c != '.' && c != '-' && c != '=')
    return c; /* not a number */
  if (c == '=')
    return VARSET;

  if (c == '-') {
    int next = line[line_index++];
    if (next == ' ' || next == '\t' || next == '\n') {
      line_index--;
      return c; // return op
    } else if (!isdigit(next) && next != '.')
      return next; // not a number
    else
      s[++i] = c = next;
  }

  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = line[line_index++]))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = line[line_index++]))
      ;
  s[i] = '\0';

  return NUMBER;
}

int get_line(char s[], int max) {
  int i = 0;
  int c;
  while ((c = getchar()) != EOF && c != '\n' && i < max) {
    s[i] = c;
    i++;
  }

  if (c == '\n') {
    s[i] = c;
    i++;
  }

  s[i] = EOF;

  return i;
}
