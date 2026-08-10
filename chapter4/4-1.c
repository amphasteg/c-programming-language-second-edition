/*
   Exercise 4-1

   Write the function strindex(s,t) which returns
   the position of the rightmost occurence of t
   in s, or -1 if there is none.
*/

#include <stdio.h>

int strindex(char s[], char t);

int main() {
  int index;

  char t = 'a';
  char str[] = {'a', 'b', 'c', 'a', 'b', 'c', 'a', 't', 'a', '8', 'i', '\0'};

  index = strindex(str, t);

  printf("Found char %c at index %d in str %s", t, index, str);
}

int strindex(char s[], char t) {
  int index = -1;

  for (int i = 0; s[i] != '\0'; i++)
    if (s[i] == t)
      index = i;

  return index;
}
