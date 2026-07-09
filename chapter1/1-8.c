/*
 Exercise 1-8
 Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

int main()
{
  int character; 
  int newline, blanks, tabs;
  
  newline = blanks = tabs = 0;

  printf("%d", blanks);
  while ((character = getchar()) != EOF)
  {
    if (character == '\n')
      newline++;

    if (character == ' ')
    {
      blanks++;
      printf("%d", blanks);
    }

    if (character == '\t')
      tabs++;
  }
  printf("Newlines:%d\n", newline);
  printf("Blanks:%d\n", blanks);
  printf("Tabs:%d\n", tabs);
}
