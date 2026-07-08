/*
   Exercise 1-7
   Write a program that prints the value of EOF.
*/

#include <stdio.h>

int main()
{

  // To send EOF to the terminal on a Unix system, use CTRL+D
  // To send EOF to the terminal on a Windows system, use CTRL+Z
  printf("%d", EOF); //Should print -1
}
