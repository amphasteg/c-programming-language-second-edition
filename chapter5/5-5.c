/*
   Exercise 5-5

   Write versions of the library functions
   strncpy, strncat, strncmp, which operate on at
   most the first n characters of their argument
   strings. For example, strncpy(s,t,n) copies at
   most n characters of t to s. Full descriptions
   are in Appendix B.

   NOTE:
   To avoid compiler warnings, functions will be
   renamed to:

   strncpy -> strxcpy
   strxcat -> strxcat
   strncmp -> strxcmp
*/
#include <setjmp.h>
#include <stdio.h>

#define MAX 1000

char *strxcpy(char *, char *, int);
char *strxcat(char *, char *, int);
int strxcmp(char *, char *, int);

int main() {
  // Test strxcpy
  char s[MAX];
  char t[] = "This is a test string";

  strxcpy(s, t, 4);

  printf("%s\n", s);

  strxcat(s, t, 12);

  printf("%s\n", s);

  char* c1 = "ABCD";
  char* c2 = "ABCE";
  
  printf("Strcmp results:\n");
  printf("Result | n | first | second\n");
  printf("%6d | %d | %5s | %s\n", strxcmp(c1, c2, 4), 4, c1, c2);
  printf("%6d | %d | %5s | %s\n", strxcmp(c1, c1, 4), 4, c1, c1);
  printf("%6d | %d | %5s | %s\n", strxcmp(c2, c1, 4), 4, c2, c1);

}

int strxcmp(char *s, char *t, int x) {
  while (*(++s) == *(++t) && x >= 0) {
    x--;
  }

  if (x <= 0)
    return 0;
  else if (*s > *t)
    return 1;
  else
    return -1;
}

char *strxcat(char *s, char *t, int x) {
  while (*(++s))
    ;

  return strxcpy(s, t, x);
}

char *strxcpy(char *s, char *t, int x) {
  while (x > 0) {
    if (!*t)
      break;
    *s++ = *t++;
    x--;
  }

  if (x > 0)
    while (x > 0) {
      *s++ = '\0';
      x--;
    }
  else
    *s++ = '\0';

  return s;
}
