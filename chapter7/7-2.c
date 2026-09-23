/*
 * Exercise 7-2
 *
 * Write a program that will print arbitrary input
 * in a sensible way. As a minumum, it should
 * print non-graphic characters in octal or
 * hexadecimal according to loca custom, and break
 * long test lines.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COL 50

int main(int argc, char *argv[]) {
  short unsigned octal = 0;
  int c;
  int col = 0;
  char buf[MAX_COL];
  int buf_len;

  if (argc > 1) {
    if (strlen(*(argv + 1)) >= 2 &&
        'o' == *(*(argv + 1) + 2)) {
      printf("Representing non-graphical "
             "characters with octal.\n");
      octal = 1;
    } else {
      puts("Error: Optional argument (--o) not "
           "recongized");
      return EXIT_FAILURE;
    }
  }

  while ((c = getchar()) != EOF) {
    buf_len = 0;
    if (isprint(c)) {
      buf[0] = c;
      buf[1] = '\0';
      buf_len = 1;
    } else if (octal)
      buf_len =
          snprintf(buf, MAX_COL * sizeof(char),
                   " 0%o ", c) /
          sizeof(char);
    else
      buf_len =
          snprintf(buf, MAX_COL * sizeof(char),
                   " 0X%x ", c) /
          sizeof(char);

    if (buf_len < 0) {
      printf("A catastrophic error occured "
             "printing 0X%x\n",
             c);
      return EXIT_FAILURE;
    }

    if (buf_len + col > MAX_COL) {
      col = 0;
      putchar('\n');
    } else
      col += buf_len;

    fputs(buf, stdout);
  }

  return EXIT_SUCCESS;
}
