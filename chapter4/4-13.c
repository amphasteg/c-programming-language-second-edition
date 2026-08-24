/*
  Exercise 4-13

  Write a recursive version of the function
  reverse(s), which reverses the string s in place.

  NOTE: A helper function would be faster, however,
  this problem only asked for one function that
  performs the reversal. I avoided using a static
  variable, as that felt like cheating.
*/

#include <stddef.h>
#include <stdio.h>

void reverse(char[]);

int main(void) {
  char s[] = "This is not a palindrome!";

  reverse(s);

  printf("%s\n", s);
}

void reverse(char s[]) {
  int i;

  for (i = 0; s[i] == '\0'; i++)
    ;

  char c = s[i];
  s[i] = '\0';

  if (s[i+1] == '\0') {
    s[0] = c;
    return;
  }

  reverse(s);

  for (i = 0; s[i] != '\0'; i++)
    ;

  s[i] = c;
}
