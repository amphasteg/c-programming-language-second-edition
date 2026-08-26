/*
 * Exercise 5-6
 * Rewrite appropriate programs from earlier
 * chapters and exercises with pointers instead
 * of array indexing. Good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and
 * their variants (Chapters 2, 3, and 4), reverse
 * (Chapter 3), and strindex, and getop
 * (Chapter 4).
 *
 * This file only implements itoa. Check the
 * other files in this folder for the other 
 * functions.
*/
#include <stdio.h>

#define LEN 1000

void itoa(int num, char* s);

int main(void) {
  int num = -923;
  char s[LEN];

  itoa(num, s);

  printf("%s\n", s);
}

void itoa(int num, char* s) {
   long inverted;
   int sign;

   if ((sign = num) < 0)
     inverted = -num;
   else
     inverted = num;

   if (sign < 0)
     *s++ = '-';

   do 
     *s++ = inverted % 10 + '0';
   while((inverted /= 10) > 0);


   *s++ = '\0';
   
}
