/*
  Exercise 1-15
  Rewrite the temperature conversion program of Section 1.2
  to use a function for conversion
*/

#include <stdio.h>

float fahrtocelc(float fahr);

int main()
{
  float fahr;

  for (fahr = 0.0; fahr <= 300.0; fahr = fahr + 20)
    printf("%3.0f%8.1f\n", fahr, fahrtocelc(fahr));
}

float fahrtocelc(float fahr)
{
  return 5 * (fahr - 32.0) / 9;
}


