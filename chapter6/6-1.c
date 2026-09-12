/*
 * Exercise 6-1
 *
 * Our version of getword does not properly handle
 * underscores, string constants, comments, or
 * preproccessor control lines. Write a better
 * version.
 */
#include <_stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS(x) (sizeof(x) / sizeof(x[0]))

struct key {
  char *word;
  int count;
} keytab[] = {
    "#define",  0, "#if",      0, "#ifdef",   0,
    "#ifndef",  0, "#include", 0, "auto",     0,
    "break",    0, "case",     0, "char",     0,
    "const",    0, "continue", 0, "default",  0,
    "unsigned", 0, "void",     0, "volatile", 0,
    "while",    0,
};

const char allowed_chars[] = {
    '#', '*', '/', '\'', '"', '\\', '_'};

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(void) {
  int n;
  char word[MAXWORD];
  const int keys = NKEYS(keytab);

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) ||
        strchr(allowed_chars, word[0]) != NULL)
      if ((n = binsearch(word, keytab, keys)) >=
          0)
        keytab[n].count++;
  for (n = 0; n < keys; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count,
             keytab[n].word);

  return 0;
}

int binsearch(char *word, struct key tab[],
              int n) {
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getword(char *word, int lim) {
  int c, in_str_const, getch(void);
  void ungetch(int);

  char *w = word;

  while (isspace(c = getch()))
    ;

  if (c != EOF)
    *w++ = c;
  if (!isalpha(c) &&
      strchr(allowed_chars, c) == NULL) {
    *w = '\0';
    return c;
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch()) &&
        strchr(allowed_chars, *w) == NULL) {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
