/*
   Exercise 2-7
   Write a fucntion invert(x,p,n) that returns x
   with the n bits that begin at position p
   inverted (i.e. 1 changed into a 0 and
   vice versa), leaving the others unchanged.
*/

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
  unsigned x = 0b10011010;
  int n = 4;
  int p = 4;

  x = invert(x, p, n);

  printf("%d", x);
}

unsigned invert(unsigned x, int p, int n) {
  unsigned mask = ~(~0U << n) << p;
  unsigned inverted_part = ~x & mask;
  unsigned regular_part = ~mask & x;

  return inverted_part | regular_part;
}
