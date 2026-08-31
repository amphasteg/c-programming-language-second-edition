/*
 * Exercise 5-13
 *
 * Write the program tail, which prints the last
 * n lines of its input. By default, n is set to
 * 10, let us say, but it can be changed by an
 * optional argument so that tail -n prints the
 * last n lines. The program should behave
 * rationally no matter how unreasonable the
 * input or the value of n. Write the program so
 * it makes the best use of available storage;
 * lines should be stored as in the sorting
 * program of Section 5.6, not in a
 * two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_LINE_DEFAULT 10
#define MAX_LINES 5000

char *lineptr[MAX_LINES];

int readlines(char *lineptr[], int n_lines);
int writelines(char *lineptr[], int n_lines);

int main(int argc, char *argv[]) {
  int n, nlines;
  if (argc > 1) {
    if (!(n = atoi(++(argv[1]))))
      n = N_LINE_DEFAULT;
  } else
    n = N_LINE_DEFAULT;

  printf("Will print out the last %d lines\n", n);

  if ((nlines = readlines(lineptr, MAX_LINES)) >= 0) {
    printf("There were %d lines\n", nlines);
    while (n > 0) {
      printf("%s\n", lineptr[nlines-- - 1]);
      n--;
    }
  } else {
    printf("Error: input is too large\n");
    return 1;
  }
}

#define MAXLEN 1000
char *alloc(int);
int get_line(char *, int);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAX_LINES];

  nlines = 0;

  while ((len = get_line(line, MAXLEN)) > 1)
    if (nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }

  return nlines;
}

int get_line(char *s, int lim) {
  int c, i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

#define ALLOCSIZE 100000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}
