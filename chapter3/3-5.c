/*
   Exercise 3-5

   Write the function itob(n,s,b) that converts
   the integer n into a base b character
   representation in the string s. In particular,
   itob(n,s,16) formats s as a hexadecimal
   integer in s.
*/

#include <stdio.h>

#define LIMIT 1000

void itob(int n, char s[], int b);
void reverse(char s[]);
int len(char s[]);

int main() {
  int num = 3123;
  char s[LIMIT];

  itoa(num, s, 16);
  printf("Number: %d, converted string: %s", num, s);
}

void itob(int n, char s[], int b) {
  long inverted;
  int i, sign;

  if ((sign = n) < 0)
    inverted = -n;
  else
    inverted = n;
  i = 0;
  do {
    s[i++] = inverted % b + '0';
  } while ((inverted /= b) > 0);

  if (sign < 0)
    s[i++] = '-';

  s[i++] = '\0';

  reverse(s);
}

void reverse(char s[]) {
  int i = 0;
  int j = len(s) - 1;
  while (i < j) {
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    i++;
    j--;
  }
}

int len(char s[]) {
  int i;
  for (i = 0; s[i] != '\0'; i++)
    ;

  return i;
}
