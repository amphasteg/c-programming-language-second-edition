/*
   Exercise 3-4
   In a two's complement number representation,
   our version of itoa does not handle the largest
   negative number, the value of n equal to
   -(2^wordsize-1). Explain why not. Modify it to
   print that value correctly, regardless of the
   machine on which it runs.

   EXPLANATION: In a two's complement number
   system, you can only represent a range from
   -(n-1) to n (e.g. -128 to 127). Since the program
   inverts n, it can only invert a value that is
   a max of -n correctly.

   This explanation from StackOverflow also helps:
   https://stackoverflow.com/questions/39258583/kr-exercise-3-4-negative-numbers-represented-in-binary
 */

#include <limits.h>
#include <stdio.h>

#define LIMIT 1000

void itoa(int n, char s[]);
void reverse(char s[]);
int len(char s[]);

int main() {
  int num = INT_MIN;
  char s[LIMIT];

  itoa(num, s);
  printf("Number: %d, converted string: %s", num, s);
}

void itoa(int n, char s[]) {
  long inverted;
  int i, sign;

  if ((sign = n) < 0)
    inverted = -n;
  else
    inverted = n;
  i = 0;
  do {
    s[i++] = inverted % 10 + '0';
  } while ((inverted /= 10) > 0);

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
