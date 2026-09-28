/*
 * Write a program to print a set of files,
 * starting each new one on a new page, with a
 * title and a running page count for each file.
 */

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#define BUFFER_SIZE 1000

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file_content(FILE *);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "At least one file must be "
                    "provided as an argument.\n");
    return EXIT_FAILURE;
  }

  FILE *file;
  int page_number = 1;

  while (--argc > 0) {
    char *filename = argv[argc];

    file = fopen(filename, "r");

    if (file == NULL) {
      fprintf(stderr,
              "There was an error opening %s, "
              "please verify it exists.\n",
              filename);
      continue;
    }

    char *content = file_content(file);

    if (ferror(file)) {
      fprintf(stderr,
              "There was an error reading the "
              "file: %s.\n",
              filename);
      continue;
    }

    fclose(file);

    printf("Title: %-15s\t\tPage: %4d", filename,
           page_number++);
  }
}

char *file_content(FILE *file) {
  if (file == NULL) {
    fprintf(
        stderr,
        "File passed to `file_content` function "
        "is null. "
        "Please verify file is not null before "
        "calling this function.\n");
    exit(EBADF);
  }
  int bufsize;

  if (BUFFER_SIZE < 2)
    bufsize = 1000;
  else
    bufsize = BUFFER_SIZE;

  char *content;
  char buf[bufsize];
  char c;
  size_t size = 0;

  while (fgets(buf, bufsize, file) != NULL) {
    size_t buf_size = sizeof(char) * strlen(buf);
    char *new = malloc(size + buf_size);
    strncpy(new, content, size);
    strncat(new, buf, buf_size);
    free(content);
    content = new;
    size += buf_size;
  }

  return content;
}
