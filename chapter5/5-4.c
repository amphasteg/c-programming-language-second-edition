/*
   Exercise 5-4

   Write the function strend(s,t), which returns
   1 if the string t occurs at the end of the
   string s, and zero otherwise.
*/

#include <stdio.h>

int strend(char *s, char *t);

int main(void) {
  char s1[] = "This is a string";
  char s2[] = "a string";
  char s3[] = "Nothing to do with s1";

  printf("The result of comparing \"%s\" and \"%s\" is %d\n", s1, s2,
         strend(s1, s2));
  printf("The result of comparing \"%s\" and \"%s\" is %d\n", s1, s3,
         strend(s1, s3));
}

int strend(char *s, char *t) {
  for (int i = 0; *(s + i); i++) {
    for (int j = 0; *(s + i + j) == *(t + j); j++) {
        if (!*(s + i + j) && !*(t + j))
          return 1;
    }
  }
  return 0;
}
