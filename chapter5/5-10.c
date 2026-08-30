/*
 * Exercise 5-10
 *
 * Write the program expr, which evaluates a
 * reverse Polish expression from the command
 * line, where each operator or operand is a
 * separate argument. For example, expr 2 3 4 + *
 * evaluates 2 * (3+4).
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char*);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
  int type;
  double op2;
  char s[MAXOP];

  for (int i = 1; i <= argc; ) {
  }
}
