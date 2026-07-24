/*
   Exercise 2-9
   In a two's complement number system, x &= (x-1)
   deletes the rightmost 1-bit in x. Explain why.
   Use this observation to write a faster version
   of bitcount.

   Exaplanation:

   For this example, let's say x = 10101010

   If we do x-1, that is equal to:
   10101010 - 00000001

   Or in two's complement
   10101010 + 11111110

   This equates to being 10101001.

   If we take 10101001 * x, we get 10101000. 

   We can use this to create a more effecient bit
   counter by repeating this operation while
   incrementing the count by one until x == 0.
*/

#include <stdio.h>

int bitcount(unsigned x);

int main() {
  unsigned x = 0b10101010;

  printf("%d\n", bitcount(x)); //Prints '4'
}

int bitcount(unsigned x) {
  int count = 0;
  while (x != 0) {
    count += 1;

    x &= (x-1);
  }

  return count;
}
