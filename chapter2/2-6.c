/*
   Exercise 2-6
   Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p
   set to the rightmost n bits of y, leaving the other bits unchanged.

   Note: This was a bit tricky for me to wrap my
   head around at first. Especially coming from
   higher level languages. The trick is to
   remember you start from position p:
  
   We start counting from the
   right-most (least-significant) bit

   To demonstrate mapping left to the top and
   right to the bottom:

   1010 1100

   Position 7: 1
   Position 6: 0
   Position 5: 1
   Position 4: 0
   Position 3: 1
   Position 2: 1
   Position 1: 0
   Position 0: 0


   We count, including p, n times starting from 1.

   In this example, if the p=2 and n=3, we would
   be modifying the bits 011.

   This also how the getbits function from the book works as well.

   Maybe this wording did not confuse you,
   but it took me a couple hours of playing around
   with the math on paper to wrap my head around it!

   Additional note: Using unsigned integers
   prevents complications with shifting
   signed integers.
*/

#include <stdio.h>

unsigned get_bits(unsigned x, int p, int n);
unsigned set_bits(unsigned x, int p, int n, unsigned y);

int main() {
  unsigned x = 0b10101010;
  unsigned y = 0b11110011;
  int p = 3;
  int n = 4;

  x = set_bits(x, p, n, y);

  //Prints the decimal number 56, (0b00111000 or 0x38)
  printf("%d", x);
}


unsigned set_bits(unsigned x, int p, int n, unsigned y) {
  unsigned bitmask = ~((~0U) << n);
  return ((bitmask & y) << p) | ((bitmask << p) & x);
}
