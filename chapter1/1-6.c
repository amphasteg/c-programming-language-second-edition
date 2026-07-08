/*
   Exercise 1-6
   Verify that the expression `getchar() != EOF` is 1 or 0.
*/

#include <stdio.h>

int main()
{
  // To send EOF to the terminal on a Unix system, use CTRL+D
  // To send EOF to the terminal on a Windows system, use CTRL+Z
  printf("%d", getchar() != EOF);
}
