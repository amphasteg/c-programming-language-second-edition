#include <stdio.h>

#define LINE_LENGTH = 1000

int getline(char line[], int max);

int main() 
{
  char input[LINE_LENGTH];

  while 

}

int getline(char s[], int limit)
{
  int c, i;

  for (i=0; i < limit-1 && (c = getchar()) != EOF && c != '\n'; i++)
   s[i] = c;

  return i;
}
