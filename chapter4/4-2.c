/*
   Exercise 4-2

   Extend atof to handle scientific notation of
   the form

   123.45e-6

   where a floating point number may be followed
   by e or E end optionally signed exponent.
*/

#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

//You can modify this array to change the number
//calculated, or, modify it to allow for an input
//string
int main() { 
  char s[] = {'1', '2', '5', '4', '5', 'e', '-', '6', '\0'};
  
  printf("%12.12f", atof(s));
}

double atof(char s[]) {
  double val, power, notation_sign;
  int i, sign, notation_val;

  for (i = 0; isspace(s[i]); i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  if (s[i] == 'e' || s[i] == 'E')
    i++;
  notation_sign = (s[i] == '-') ? .1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (notation_val = 0.0; isdigit(s[i]); i++)
    notation_val = 10 * notation_val + (s[i] - '0');

  val = sign * val / power;

  for (int j = 0; j < notation_val; j++) {
    val *= notation_sign;
  }

  return val;
}
