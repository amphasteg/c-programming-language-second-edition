/*
  Exercise 1-16
  Revise the main routine of the longest-line program
  so it will correctly print the length of arbitrary long
  input lines, and as much as possible of the text.
*/

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);

int main()
{
  int len;

  char line[MAXLINE];

  while((len = getline(line, MAXLINE)) > 0)
  {
    printf("%s", line);
    printf("Line length: %d\n", len);
  } 

  return 0;
}

int getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c = getchar()) != EOF && c!='\n'; i++)
    s[i] = c;

  s[i] = '\0';
  return i;
}
