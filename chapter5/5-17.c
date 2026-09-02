/*
 * Exercise 5-14
 *
 * Modify the sort program to handle a -r flag,
 * which indicates sorting in reverse
 * (decreasing order. Be sure that -r works with
 * -n.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void reverse_order(char *lineptr[], int nlines);
void qusort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *));
int numcmp(char *, char *);
int fstrcmp(char *, char *);
int field_strcmp(char *, char *);
// Wrapper strcmp
int wstrcmp(char *, char *);
void dstrcpy(char *, char *);

int directory = 0;
int field_index = 0;
int numeric = 0;
int reverse = 0;
int fold = 0;

int main(int argc, char *argv[]) {
  int nlines;

  while (argc-- > 0) {
    switch (*(argv[argc] + 1)) {
    case 'n':
      numeric = 1;
      break;
    case 'r':
      reverse = 1;
      break;
    case 'f':
      fold = 1;
      break;
    case 'd':
      directory = 1;
      break;
    case 'i':
      field_index = atoi((argv[argc] + 2));
      printf("Sorting on field %d\n",
             field_index);
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >=
      0) {
    int (*comp)(void *, void *);

    if (field_index > 0)
      comp =
          (int (*)(void *, void *))field_strcmp;
    else if (numeric)
      comp = (int (*)(void *, void *))numcmp;
    else
      comp = ((int (*)(void *, void *))(
          fold ? fstrcmp : wstrcmp));

    qusort((void **)lineptr, 0, nlines - 1, comp);

    if (reverse)
      reverse_order(lineptr, nlines);

    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("Input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000
int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;

  // Changed this to one to stop reading after the
  // user enters \n rather than ^Z
  while ((len = get_line(line, MAXLEN)) > 1)
    if (nlines >= maxlines ||
        (p = alloc(len)) == NULL)
      return -1;
    else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

void swap(void *v[], int, int);

void qusort(void *v[], int left, int right,
            int (*comp)(void *, void *)) {
  int i, last;
  void swap(void *v[], int, int);
  if (left >=
      right) /* do nothing if array contains */
    return;  /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qusort(v, left, last - 1, comp);
  qusort(v, last + 1, right, comp);
}

void reverse_order(char *lineptr[], int nlines) {
  int i;
  int j = nlines - 1;
  for (i = 0; i < j; i++) {
    swap((void **)lineptr, i, j);
    j--;
  }
}

void swap(void *v[], int i, int j) {
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int get_line(char s[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 &&
              (c = getchar()) != EOF && c != '\n';
       ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

int numcmp(char *s1, char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

int field_strcmp(char *s1, char *s2) {
  int start1 = 0;
  int start2 = 0;
  int end1 = 0;
  int end2 = 0;
  int f = field_index;

  printf("s1 = %s s2 = %s\n", s1, s2);
  while (f) {
    if (*(s1 + start1) == '\0')
      break;
    if (*(s1 + start1) == ' ')
      f--;
    else
      start1++;
  }

  f = field_index;

  while (f) {
    if (*(s2 + start2) == '\0')
      break;
    if (*(s2 + start2) == ' ')
      f--;
    else
      start2++;
  }

  start1++;
  start2++;

  while (*(s1 + start1 + end1) != ' ' &&
         *(s1 + start1 + end1) != '\0')
    end1++;

  while (*(s2 + start2 + end2) != ' ' &&
         *(s2 + start2 + end2) != '\0')
    end2++;

  printf("start1=%d end1=%d start2=%d end2=%d\n",
         start1, end1, start2, end2);
  char *c1 = alloc(end1 + 1);
  char *c2 = alloc(end2 + 1);

  s1 += start1;
  *(s1 + end1 + 1) = '\0';
  s2 += start2;
  *(s2 + end2 + 1) = '\0';

  // TODO undo this pointer stuff cause it
  // destroys everything
  strcpy(c1, s1);
  printf("c1 = %s", c1);
  strcpy(c2, s2);
  printf(" c2 = %s\n", c2);

  printf("Comparing fields c1=%s and c2=%s\n", c1,
         c2);

  if (numeric)
    return numcmp(c1, c2);
  if (fold)
    return fstrcmp(c1, c2);

  return strcmp(c1, c2);
}

int wstrcmp(char *s1, char *s2) {
  if (!directory) {
    return strcmp(s1, s2);
  }

  char *c1 = alloc(strlen(s1));
  char *c2 = alloc(strlen(s2));

  dstrcpy(s1, c1);
  dstrcpy(s2, c2);

  return strcmp(c1, c2);
}

void dstrcpy(char *s, char *d) {
  while (*s++)
    if (!isdigit(*s) && !(*s > 'a' || *s > 'z') &&
        !(*s > 'A' && *s < 'Z') && (*s != ' '))
      continue;
    else
      *d++ = *s;

  *d = '\0';
}

int fstrcmp(char *s1, char *s2) {
  char *c1 = alloc(strlen(s1));
  char *c2 = alloc(strlen(s2));

  strcpy(c1, s1);
  strcpy(c2, s2);

  for (int i = 0; *(c1 + i); i++)
    *(c1 + i) = toupper(*(c1 + i));

  for (int i = 0; *(c2 + i); i++)
    *(c2 + i) = toupper(*(c2 + i));

  return wstrcmp(c1, c2);
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}
