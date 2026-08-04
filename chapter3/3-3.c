/*
   Exercise 3-3

   Write a function expand(s1, s2) that expands
   shorthand notations like a-z in the string s1
   into the equivalent complete list abc..xyz in
   s2. Allow for letters of either case and
   digits, and be prepared to handle cases like
   a-b-c and a-z0-9 and -a-z. Arrange that a
   leading or trailing - is taken literally.

   NOTE: You could consider this to be a
   prototype solution. With some refactoring,
   you could create something that has less
   conditions and is more concise.
   }
*/

#include <stdio.h>

#define LIMIT 1000
#define TRUE (1 == 1)
#define FALSE !TRUE
#define NOT_SET -1

void expand(char s1[], char s2[]);
int get_str(char str[], int limit);

int main(void) {
  char string[LIMIT], expanded[LIMIT];
  get_str(string, LIMIT);

  expand(string, expanded);

  printf("Expanded: %s", expanded);
}

int get_str(char str[], int limit) {
  int c, i;

  i = 0;

  while ((c = getchar()) != '\n' && i < limit) {
    str[i] = c;
    i++;
  }

  str[i] = '\0';
  return i + 1;
}

void expand(char str[], char expanded[]) {
  int to, from, len, dash;

  len = 0;
  to = from = NOT_SET;
  dash = FALSE;

  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9')) {
      if (dash) {
        to = c;

        if (from == NOT_SET) {
          if (c >= 'a' && c <= 'z')
            from = 'a';
          else if (c >= 'A' && c <= 'Z')
            from = 'A';
          else if (c >= '0' && c <= '9')
            from = '0';
        }

        while (from <= to) {
          expanded[len] = from;
          from++;
          len++;
        }
        dash = FALSE;
        from = to + 1;
        to = NOT_SET;
      } else
        from = c;

    } else if (c == '-') {
      dash = TRUE;
      if (str[i + 1] == '\0') {
        if (c >= 'a' && c <= 'z')
          to = 'z';
        else if (c >= 'A' && c <= 'Z')
          to = 'Z';
        else if (c >= '0' && c <= '9')
          to = '9';

        while (from <= to) {
          expanded[len] = from;
          from++;
          len++;
        }
      }
    }
  }
  expanded[len] = '\0';
}
