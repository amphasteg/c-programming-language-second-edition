/*
   Exercise 1-17
   Write a program to print all input lines that are longer than 80 characters
*/
#include <stdio.h>

#define LINE_LENGTH = 1000

int getline(char line[], int max);

int main() 
{
  char input[LINE_LENGTH];

  int len = 0;

  while((len = getline(input, LINE_LENGTH)) > 0)
  {
    if (len > 80)
      printf("%s", input);
  } 

}

