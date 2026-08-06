/*
   Exercise 3-6

   Write a version of itoa that accepts three
   arguments instead of two. The third argument
   is a minimum field width; the converted number
   must be padded with blanks on the left if 
   necessary to make it wide enough.
*/

#include <stdio.h>

#define LIMIT 1000

void itoa(int n, char s[], int w);
void reverse(char s[]);
int len(char s[]);

int main() {
  int num = -255;
  int w = 5;
  char s[LIMIT];

  itoa(num, s, w);
  printf("Number: %d, converted string: %s", num, s);
}

void itoa(int n, char s[], int w) {
  long inverted;
  int i, sign;

  if ((sign = n) < 0)
    inverted = -n;
  else
    inverted = n;
  i = 0;
  do {
    s[i++] = inverted % 10 + '0';
    w--;
  } while ((inverted /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';

  while (w != 0) {
    s[i++] = ' ';
    w--;
  }

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
