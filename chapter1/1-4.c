/*
   Exercise 1-4
   Write a program to print the corresponding Celsius to Fahrenheit table.
*/

#include <stdio.h>

int main()
{
  float fahr, celsius;
  float lower, upper, step;

  lower = -18;
  upper = 150;
  step = 11;

  celsius = lower;
  
  printf("Fahrenheit\tCelsius\n");
  printf("------------------------\n");
 
  while (celsius <= upper)
  {
    fahr = celsius * (9.0/5.0) + 32.0;
    printf("%3.1f%20.1f\n", fahr, celsius);
    celsius = celsius + step;
  }
}
