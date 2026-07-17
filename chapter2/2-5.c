/*
   Exercie 2-5
   Write the fucntion any(s1, s2), which returns the first location of a string s1
   where any character from the string s2 occurs, or -1 if s1 contains no characters
   from s2. (The standard library function strpbrk does the same job but returns a
   pointer to the location).
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000

int get_str(char str[], int limit);
int any(char s1[], char s2[]);

int main() {
  char s1[MAX], s2[MAX];

  printf("Enter the first string\n");
  get_str(s1, MAX);

  printf("Enter the second string\n");
  get_str(s2, MAX);

  printf("Location: %d", any(s1, s2));
}

int get_str(char str[], int limit) {
  int i, c;

  for (i = 0; (c = getchar()) != EOF && c != '\n' && i < limit; i++)
    str[i] = c;

  str[i] = '\0';

  return i;
}

int any(char s1[], char s2[]) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);

  for (int i = 0; i < len1; i++)
    for (int j = 0; j < len2; j++)
      if (s1[i] == s2[j])
        return i + 1;

  return -1;
}
