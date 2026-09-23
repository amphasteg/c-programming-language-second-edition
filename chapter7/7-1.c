/*
 * Exercise 7-1
 *
 * Write a program that converts upper case to
 * lower or lower case to upper, depending on the
 * name it is invoked with, as found in argv[0].
 *
 * NOTE: For the ease of use and convenience, this
 * program will check for "lower" or "upper" in
 * the second argument, rather than argv[0]
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPPER "upper"
#define LOWER "lower"
#define PROG *(argv + 1)

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(
        "Error: program needs to be called with "
        "argument \"lower\" or \"upper\"\n");
    return EXIT_FAILURE;
  }

  int c;
  if (strcmp(PROG, LOWER) == 0)
    while ((c = getchar()) != EOF && c != '\n')
      putchar(tolower(c));
  else if (strcmp(PROG, UPPER) == 0)
    while ((c = getchar()) != EOF && c != '\n')
      putchar(toupper(c));
  else {
    printf("Program was called under the name "
           "\"%s\". Please call it under the "
           "name \"upper\" or \"lower\".",
           PROG);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
