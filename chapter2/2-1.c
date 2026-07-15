/*
  Exercise 2-1
  Write a program to determine the ranges of char, short, in, and
  long variables, both signed and unsigned, by printing the appropriate
  values from standard headers and by direct computation. Harder if you
  compute them: determine the ranges of the various floating point types.
*/

#include <float.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

int main() {
 //Standard lib values
  //Char maxes
  printf("Char max from standard lib %d\n", CHAR_MAX);
  printf("Unsigned char max from standard lib: %d\n", UCHAR_MAX);
  printf("Signed char max from standard lib: %d\n", SCHAR_MAX);

  //Char mins
  printf("Char min from standard lib: %d\n", CHAR_MIN);
  printf("Singed char min from standard lib: %d\n", SCHAR_MIN);

  //The min of anything unsigned should realistically be 0
  printf("Unsigned char min from standard lib: %d\n", 0);  

  //Int maxes
  printf("Int max from standard lib: %d\n", INT_MAX);
  printf("Unsignd int max from standard lib: %d\n", UINT_MAX);

  //Int mins
  printf("Int min from standard lib: %d\n", INT_MIN);
  printf("Unsigned int min from standard lib: %d\n", 0);

  //Long int maxes
  printf("Long max from standard lib: %ld\n", LONG_MAX);
  printf("Unsinged long max from standard lib: %lu\n", ULONG_MAX);

  //Long int mins
  printf("Long min from standard lib: %ld\n", LONG_MIN);

  //Float maxes
  printf("Float max from standard lib: %f\n", FLT_MAX);

  //Float min
  printf("Float min from standard lib:%f\n", FLT_MIN);

  //Double max
  printf("Double max from standard lib: %f\n", DBL_MAX);
  printf("Long double max from standard lib: %Lf\n", LDBL_MAX);

  //Double min
  printf("Double min from standard lib: %f\n", DBL_MIN);
  printf("Long double min from standard lib: %Lf\n", LDBL_MIN);
  

  //Computing the values. This method of doing it takes a while...
  //Add print statements to feel like you're in the matrix!
  int standard_int, int_max, int_min;
  unsigned int uint, uint_min, uint_max;
  signed int sint, sint_max, sint_min;
  long int lint, lint_max, lint_min;
  unsigned long int ulint, ulint_max, ulint_min;
  signed long int slint, slint_max, slint_min;

  char standard_char, char_max, char_min;
  unsigned char uchar, uchar_max, uchar_min;
  signed char schar, schar_max, schar_min;

  float standard_float, float_max, float_min;
  
  double standard_double, double_max, double_min;
  long double ldouble, ldouble_max, ldouble_min; 

  for (standard_int = 1; standard_int != 0; standard_int++) {
    if (standard_int > int_max)
      int_max = standard_int;

    if (standard_int < int_min)
      int_min = standard_int;
  }

  for (uint = 1; uint != 0; uint++) {
    if (uint > uint_max)
      uint_max = uint;

    if (uint < uint_min)
      uint_min = uint;
  }

  for (sint = 1; sint != 0; sint++) {
    if (sint > sint_max)
      sint_max = sint;

    if (sint < sint_min)
      sint_min = sint;
  }

  for (lint = 1; lint != 0; lint++) {
    if (lint > lint_max)
      lint_max = lint;

    if (lint < lint_min)
      lint_min = lint;
  }

  for (ulint = 1; lint != 0; lint++) {
    if (ulint > ulint_max)
      ulint_max = ulint;

    if (ulint < ulint_min)
      ulint_min = ulint;
  }

  for (slint = 1; slint != 0; slint++) {
    if (slint > slint_max)
      slint_max = slint;

    if (slint < slint_min)
      slint_min = slint;
  }

  for (standard_char = 1; standard_char != 0; standard_char++) {
    if (standard_char > char_max)
      char_max = standard_char;

    if (standard_char < char_min)
      char_min = standard_char;
  }

  for (uchar = 1; uchar != 0; uchar++) {
    if (uchar > uchar_max)
      uchar_max = uchar;

    if (uchar < uchar_min)
      uchar_min = uchar;
  }

  for (schar = 1; schar != 0; schar++) {
    if (schar > schar_max)
      schar_max = schar;

    if (schar < schar_min)
      schar_min = schar;
  }
  for (standard_float = .000001; standard_float != 0.000000; 
      standard_float+=0.000001) {
    if (standard_float > float_max)
      float_max = standard_float;

    if (standard_float < float_min)
      float_min = standard_float;
  }

  for (standard_double = 0.000001; standard_double != 0.000000;
      standard_double += 0.000001) {
    if (standard_double > double_max)
      double_max = standard_double;

    if (standard_double < double_min)
      double_min = standard_double;
  }

  for (ldouble = 0.000001; ldouble != 0.000000;
      ldouble += 0.000001) {
    if (ldouble > ldouble_max)
      ldouble_max = ldouble;

    if (ldouble < ldouble_min)
      ldouble_min = ldouble;
  }

  //Computed int maxes
  printf("Computed max int: %d\n", int_max);
  printf("Computed max long int: %ld\n", lint_max);
  printf("Computed max unsigned int: %d\n", uint_max);
  printf("Computed max signed int: %d\n", sint_max);
  printf("Computed max unsigned long int: %ld\n", ulint_max);
  printf("Computed max signed long int: %ld\n", slint_max);

  //Computed in mins
  printf("Computed min int: %d\n", int_min);
  printf("Computed min long: %ld\n", lint_min);
  printf("Computed min unsigned int: %d\n", uint_min);
  printf("Computed min signed int: %d\n", sint_min);
  printf("Computed min unsigned long int: %ld\n", ulint_min);
  printf("Computed min signed long int: %ld\n", slint_min);

  //Computed char maxes
  printf("Computed max char: %d\n", char_max);
  printf("Computed max signed char: %d\n", schar_max);
  printf("Computed max unsigned char: %d\n", uchar_max);

  //Computed char mins
  printf("Computed min char: %d\n", char_min);
  printf("Computed min signed char: %d\n", schar_min);
  printf("Computed min unsigned char: %d\n", uchar_min);

  //Computed float max
  printf("Computed float max: %f\n", float_max);

  //Computed float min
  printf("Computed float min: %f\n", float_min);

  //Computed double maxes
  printf("Computed double max: %f\n", double_max);
  printf("Computed long double max: %Lf\n", ldouble_max);

  //Computed double mins
  printf("Computed double min: %f\n", double_min);
  printf("Computed long double max: %Lf\n", ldouble_min);
}

