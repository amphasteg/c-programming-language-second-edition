/*
 * Write a program to print a set of files,
 * starting each new one on a new page, with a
 * title and a running page count for each file.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syslimits.h>

#define BUFFER_SIZE 100

char *file_content(FILE*);

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


  }
}

char *file_content(FILE *file) {
  char *content;
  char buf[LINE_MAX];
  char c;
  size_t size = 0;

  while (fgets(buf, LINE_MAX, file) != NULL) {
    size_t buf_size = sizeof(char) * strlen(buf);
    char* new = malloc(size + buf_size);
    strncpy(new, content, size);
    strncat(new, buf, buf_size);
    free(content);
    content = new;
    size += buf_size;
  }
  
}
