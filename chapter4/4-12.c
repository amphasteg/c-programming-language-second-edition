/*
Exercise 4-12

Adapt the ideas of printd to write a recursive
version of itoa; that is, convert an integer into
a string by calling a recursive routine.
*/

#include <stdio.h>

#define MAX_LEN 1000

void itoa(int, char[]);

int main(void) {
  int num = 3258;
  char s[MAX_LEN];

  itoa(num, s);
  printf("%s", s);
}

void itoa(int n, char s[]) {
  static int i = 0;
  if (n < 0) {
    s[i++] = '-';
    n = -n;
  }

  s[i++] = n % 10 + '0';
  if (n / 10)
    itoa(n / 10, s);

  s[i++] = '\0';
}
