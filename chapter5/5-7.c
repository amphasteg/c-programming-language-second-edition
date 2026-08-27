/*,
 * Exercise 5-7
 *
 * Rewrite readlines to store lines in an array
 * supplied by main, rather than calling alloc to
 * maintain storage. How much faster is the
 * program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXCHARS 10000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char *, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineprt[], int left, int right);

int main(void) {
  int nlines;
  char chars[MAXCHARS];

  if ((nlines = readlines(lineptr, chars, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Error: input too big to sort\n");
    return 1;
  }

  return 0;
}

#define MAXLEN 1000

int getline(char *, int);

int readlines(char *lineptr[], char *p, int maxlines) {
  int len, nlines, poffset;
  char line[MAXLEN];

  nlines = 0;
  poffset = 0;

  while ((len = getline(line, MAXLEN)) > 0)
    if (nlines >= maxlines || poffset + len > MAXCHARS)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p + poffset, line);
      lineptr[nlines++] = p + poffset;
      poffset += len;
    }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

int getline(char *line, int max) {
  int c, i;

  for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *(line + i) = c;

  if (c == '\n') {
    *(line + i) = c;
    i++;
  }

  *(line + i) = '\0';

  return i;
}

void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
