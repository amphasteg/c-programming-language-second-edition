/*
   Exercise 1-4

   Write an alternative version of squeeze(s1, s2) that deletes each character
   in s1 that matches any character in the string s2.
*/

#include <string.h>
#include <stdio.h>

#define MAX 1000
#define TRUE (1==1)
#define FALSE !TRUE

int get_str(char str[], int limit);
int squeeze(char s1[], char s2[]);

int main() {
  char str1[MAX], str2[MAX];
  int final_len;

  printf("Enter the first line:\n");
  get_str(str1, MAX);

  printf("Enter the second line:\n");
  get_str(str2, MAX);

  final_len = squeeze(str1, str2);

  printf("Final length: %d\nFinal string: %s\n", final_len, str1);
}

int get_str(char str[], int limit) {
  int i, c;

  for (i = 0; (c = getchar()) != EOF && i < limit; i++)
    str[i] = c;

  str[i] = '\0';


  return i;
}

int squeeze(char s1[], char s2[]) {
  int new_len = 0;
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  
  for (int i = 0; i < len1; i++) {
    char c1 = s1[i];
    int str_has = FALSE;
    for (int j = 0; j < len2; j++) {
      if (c1 == s2[j])
        str_has = TRUE;
    }
    if (str_has == FALSE) {
      s1[new_len] = c1; 
      new_len++;
    }

    str_has = FALSE;
  }

  s1[new_len] = '\0';

  return new_len;
}
