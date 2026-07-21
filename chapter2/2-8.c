/*
   Exercise 2-8
   Write a fucntion rightrot(x,n) that returns the
   value of the integer x rotated to the right
   by n positions.
*/

#include <stdio.h>
#include <limits.h>

unsigned right_rot(unsigned x, int n);
int unsigned_len();

int main() {
  unsigned x = 0b10011010;
  int n = 2;

  right_rot(x, n);
}

unsigned right_rot(unsigned x, int n) {
  int len = unsigned_len();

  n = n % len;
  unsigned final_n_bits = ~(~0U << n) & x;
  x = x >> n;
  x = x | (final_n_bits << (len - n));
  return x;
}

int unsignd_len() {
  unsigned int x = ~0U;
  int len = 0;
  while (x!= 0) {
    x = x >> 1;
    len++;
  }
  return len;
}
