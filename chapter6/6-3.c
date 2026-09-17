/*
 * Exercise 6-3
 *
 * Write a cross-referencer that prints a list of
 * all words in a document and for each word, a
 * list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so
 * on.
 */

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF 100
#define MAXWORD 80

struct word_node {
  struct line_list *line_occurences;
  char *word;
  struct word_node *left;
  struct word_node *right;
};

struct line_list {
  int length;
  int *list;
};

const char *noise_words[] = {
    "the", "and", "that", "it", "to", "at", "it"};

int is_noise_word(char *);
struct word_node *add_tree(struct word_node *,
                           char *, int);
void print_tree(struct word_node *);
int getword(char *, int);
void add_line(struct line_list *, int);
struct word_node *talloc();
char getch(void);
void ungetch(char);
int int_cmp(const void *, const void *);

char buf[BUF];
int bufp = 0;

int main(void) {
  struct word_node *tree;
  char word[MAXWORD];
  int line = 0;

  while (getword(word, MAXWORD - 1) != EOF) {
    if (word[0] == '\n') {
      line++;
      continue;
    }
    tree = add_tree(tree, word, line);
  }
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
    if (!isalnum(*w = getch())) {
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

struct word_node *add_tree(struct word_node *p,
                           char *word, int line) {
  if (p == NULL) {
    p = talloc();
    p->word = word;
    add_line(p->line_occurences, line);
    p->left = NULL;
    p->right = NULL;
  }

  return p;
}

void add_line(struct line_list *list, int line) {
  if (bsearch(&line, list->list, list->length,
              sizeof(list->list[0]),
              int_cmp) != NULL)
    return;

  list->length++;
  int *new_list =
      malloc(sizeof(int) + list->length);

  int *list_p = list->list;

  for (int i = 0; i < list->length; i++) {
    if (i + 1 >= list->length && *list_p < line) {
      new_list[i++] = *list_p;
      new_list[i] = line;
    }
    else if (*list_p < line && *(list_p+1) > line) {
      new_list[i++] = *list_p++;
      new_list[i] = *list_p++;
    }
    else
      new_list[i] = *list_p++;
  }

  list_p = list->list;
  list->list = new_list;

  free(list_p);
}

int int_cmp(const void *p1, const void *p2) {
  int *key = (int *) p1;
  int *comp = (int *) p2;

  if (*key < *comp)
    return -1;
  else if (*key > *comp)
    return 1;

  return 0;
}
