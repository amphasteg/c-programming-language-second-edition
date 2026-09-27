/*Exercise 7-7
 *
 * Modify the pattern finding program of Chapter 5
 * to take its input from a set of named files or,
 * if no files are named as arguments, from the
 * standard input. Should the file name be printed
 * when a matching line is found?
 */

#include <stdio.h>
#include <stdlib.h>

int find_pattern(const char*, FILE*);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Invalid arguments. Program usage: <program> pattern file1, file2, ...\n Minimum of 2 arguments, only %d provided.\n", argc - 1);
    exit(1);
  }

  while (--argc > 0) {
    FILE *fp = fopen(argv[argc], "r");

  }
  
}


