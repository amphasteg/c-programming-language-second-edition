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
#include <string.h>

int find_pattern(const char *, FILE *);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr,
            "Invalid arguments. Program usage: "
            "./program pattern --file1 --file2, "
            "...\n Minimum of 2 arguments, only "
            "%d provided.\n",
            argc - 1);
    exit(1);
  }

  const char *pattern = argv[1];

  //Use stdin
  if (argc == 2) {
    int line = find_pattern(pattern, stdin);

    if (line < 1)
      printf("The pattern \"%s\" was not found "
             "in the text entered.\n",
             pattern);
    else
      printf("The pattern \"%s\" was found in "
             "the text entered.\n",
             pattern);
  } else //Check files entered
    while (--argc > 1) {
      // Add two to pointer for the double --
      char *file_name = argv[argc--] + 2;
      FILE *fp = fopen(file_name, "r");

      if (fp == NULL) {
        fprintf(stderr,
                "Could not find the file \"%s\", "
                "make sure it exists.\n",
                file_name);
        continue;
      }

      int line = find_pattern(pattern, fp);

      if (ferror(fp))
        fprintf(stderr,
                "There was an error reading from "
                "the file \"%s\".\n",
                file_name);
      else if (line < 1)
        printf("The pattern \"%s\" was not found "
               "in file \"%s\".\n",
               pattern, file_name);
      else
        printf("The pattern \"%s\" was found in "
               "file \"%s\" at line %d.\n",
               pattern, file_name, line);

      fclose(fp);
    }

  return 0;
}

/* Finds a pattern in a given file. Returns the
 * line the pattern was found, or 0 if not
 * found.
 */
int find_pattern(const char *pattern, FILE *fp) {
  char c;
  int pattern_length;
  int pattern_count = 0;
  int line_num = 1;

  pattern_length = strlen(pattern);

  while ((c = fgetc(fp)) != EOF &&
         pattern_count < pattern_length) {
    if (c == '\n') {
      line_num++;
      pattern_count = 0;
    } else if (c == pattern[pattern_count])
      pattern_count++;
    else
      pattern_count = 0;
  }

  if (pattern_count == pattern_length)
    return line_num;
  else
    return 0;
}
