/*
 * Exercise 6-5
 *
 * Write a function undef that will remove a name
 * and definition from the tabl maintained by
 * lookup and install.
 */
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define BUF 100
#define LIM 100

#ifdef _WIN32
#define STRDUP(w) _strdup(w)
#else
#define STRDUP(w) strdup(w)
#endif

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);
int getword(char *, int);
char getch(void);
void ungetch(char);

char buf[BUF];
char *word;
int bufp = 0;

int main(void) {
  while(getword(word, LIM) != EOF || strcmp(word, "END") != 0)
    if (strcmp("#define", word) == 0) {
      getword(word, LIM);
      char *name = strdup(word);
      getword(word, LIM);
      install(name, word);
    }
    else if (strcmp("#undef", word) == 0) {
      getword(word, LIM);
      undef(word);
    }
}

unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL;
       np = np->next)
    if (strcmp(s, np->name) == 0)
      return np;

  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) {
    np = malloc(sizeof(*np));
    if (np == NULL ||
        (np->name = STRDUP(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else
    free(np->defn);

  if ((np->defn = STRDUP(defn)) == NULL)
    return NULL;

  return np;
}

int undef(char *name) {
  struct nlist *current;
  unsigned hashval;

  if ((current = lookup(name)) == NULL) {
    printf("Attempted to delete name \"%s\", but "
           "it was not found.\n",
           name);
    return 0;
  }
  struct nlist *next = current->next;

  free(current->name);
  free(current->defn);

  if (next != NULL) {
    current->name = next->name;
    current->defn = next->defn;
    current->next = next->next;
  } else 
    free(current);

  return 1;
}

int getword(char *word, int lim) {
  int c;
  char *w = word;

  while (isspace(c = getch()))
    if (c == '\n') {
      *w++ = c;
      *w = '\0';
      return word[0];
    }

  if (c != EOF)
    *w++ = c;
  for (; --lim > 0; w++)
    if (!isalnum(*w = getch()) || *w == '#') {
      ungetch(*w);
      break;
    }

  *w = '\0';
  return word[0];
}

char getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(char c) {
  if (bufp >= BUF)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
