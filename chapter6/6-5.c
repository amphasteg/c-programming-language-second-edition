/*
 * Exercise 6-5
 *
 * Write a function undef that will remove a name
 * and definition from the tabl maintained by
 * lookup and install.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101

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

int main(void) {
    install("TEST", "test");

    // Install other collision values for the same hash as for "TEST" -> 51.
    install("TSHe", "test1");
    install("UPXD", "test2");
    install("9iww", "test3");
    install("mY1a", "test4");
    install("uuoT", "test5");

    struct nlist *node_p = lookup("TEST");
    if (node_p == NULL) {
        puts("Error: hash value not found.");
    } else {
        printf("%s: %s\n", node_p->name, node_p->defn);
        if (undef("TEST") && lookup("TEST") == NULL) {
            printf("'%s' was undefined successfully.\n", "TEST");
        } else {
            printf("Error: failed to undefine '%s'.\n", "TEST");
        }
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
