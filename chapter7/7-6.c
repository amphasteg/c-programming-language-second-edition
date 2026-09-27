/*
 * Exercise 7-6
 *
 * Write a program to compare two files, printing
 * the first line where they differ.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fcomp(FILE *f1, FILE *f2);
void append(char **, char);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr,
            "Program requires to files as "
            "argument, %d were provided.\n",
            argc - 1);
    return EXIT_FAILURE;
  }

  FILE *fp1;
  FILE *fp2;

  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");

  if (fp1 == NULL) {
    fprintf(stderr, "Error opening file: %s\n",
            argv[1]);
    return EXIT_FAILURE;
  }

  if (fp2 == NULL) {
    fprintf(stderr, "Error opening file %s\n",
            argv[2]);
    return EXIT_FAILURE;
  }

  fcomp(fp1, fp2);

  fclose(fp1);
  fclose(fp2);

  return EXIT_SUCCESS;
}

void fcomp(FILE *f1, FILE *f2) {
  char *line1;
  char *line2;
  int line_num = 1;

  line1 = malloc(sizeof(char));
  line2 = malloc(sizeof(char));

  if (line1 == NULL || line2 == NULL) {
    fprintf(
        stderr,
        "Error allocating memory for lines.\n");
    exit(1);
  }

  *line1 = '\0';
  *line2 = '\0';

  int c1, c2;

  while ((c1 = fgetc(f1)) != EOF &&
         (c2 = fgetc(f2)) != EOF) {
    // Stop if lines are not equal
    if (c1 != c2)
      break;
    // If c1 and c2 are new line, we can assume
    // this line is equal, and reset for the next.
    else if (c1 == '\n') {
      *line1 = '\0';
      *line2 = '\0';
      line_num++;
    }
    // If not a newline and equal, append to a new
    // string.
    else {
      append(&line1, c1);
      append(&line2, c2);
    }
  }

  if (ferror(f1) || ferror(f2)) {
    fprintf(
        stderr,
        "There was an error reading the files.");
    exit(EXIT_FAILURE);
  }

  const int c1_EOF = (c1 == EOF);
  const int c2_EOF = (c2 == EOF);

  if (strcmp(line1, line2) == 0 && c1_EOF &&
      c2_EOF) {
    printf(
        "Contents are identical. No differences "
        "were found.\n");
    return;
  }

  // Get the rest of the line to print
  if (!c1_EOF) {
    append(&line1, c1);
    while ((c1 = fgetc(f1)) != EOF && c1 != '\n')
      append(&line1, c1);
  }
  if (!c2_EOF) {
    append(&line2, c2);
    while ((c2 = fgetc(f2)) != EOF && c1 != '\n')
      append(&line2, c2);
  }

  printf("Found difference at line %d:\n%s\n%s\n",
         line_num, line1, line2);
}

// Takes a pointer a string (char pointer) and
// reassigns it to a with the added char
void append(char **s, char c) {
  if (s == NULL) {
    fprintf(stderr,
            "Error: cannot append %c to null "
            "string.\n",
            c);
    exit(1);
  }

  // Length of string plus spot for new char and
  // null char
  int len = strlen(*s) + 2;

  char *new = malloc(len * sizeof(char));

  if (new == NULL) {
    fprintf(stderr,
            "Error appending %c to %s: unable to "
            "assign memory.\n",
            c, *s);
    exit(1);
  }

  strncpy(new, *s, len); // {s, '\0', '\0'}

  new[len - 2] = c; //{..., c, '\0'}
  free(*s);
  *s = new;
}
