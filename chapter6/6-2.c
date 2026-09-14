/*
 * Exercise 6-2
 *
 * Write a program that reads a C program and
 * prints in alphabetical order each group of
 * varaible names that are identical in the first
 * 6 characters, but different somewhere
 * thereafter. Don't cound words within strings
 * and comments. Make 6 a parameter that can be
 * set from the command line.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 100

struct word {
  char *word;
  struct word *left;
  struct word *right;
};

struct first_chars {
  struct word *root_word;
  struct first_chars *left;
  struct first_chars *right;
};

// Types that will always come before a variable
// name, and if not, then it is not a var.
// e.g. 'int x' is a var,
// but func(int) is not.
const char *suffix_types[] = {"int", "char",
                              "float", "double"};
// Types that can be used alongside a suffix type
// or on their own.
// e.g. long int x OR long x
const char *dual_types[] = {"long", "unsigned",
                            "signed"};
// Types cannot be used on their own and most
// always preceed a var type.
// e.g. const int x
const char *prefix_types[] = {"const", "static",
                              "extern", "struct"};

// Number of identical chars. Defaults to 6
int n_chars = 6;

int check_args(int, char *[]);
int getword(char *, int);

int main(int argc, char *argv[]) {
  if (check_args(argc, argv) == -1)
    return -1;
}

// Verifies arguments are formatted correctly and
// sets n if they are
int check_args(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Too many arguments : %d. The only "
           "argument for this program is --n; "
           "where n is the number of identical "
           "characters to look for.",
           argc);
    return -1;
  } else if (argc == 2) {
    if (*argv[1] != '-' &&
        *(argv[1] + 1) != '-') {
      printf("Optional argument must be "
             "preceeded by \"--\"");
      return -1;
    }

    // Remove the '--'
    char *char_num = argv[1] + 2;

    // Assign and check if is a number
    int temp_num = atoi(char_num);

    if (temp_num > 0)
      n_chars = temp_num;
    else {
      printf("The argument provided is not a "
             "number: %s",
             char_num);
      return -1;
    }
  }

  return 0;
}


