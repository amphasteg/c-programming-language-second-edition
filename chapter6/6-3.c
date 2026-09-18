/*
 * Exercise 6-3
 *
 * Write a cross-referencer that prints a list of
 * all words in a document and for each word, a
 * list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so
 * on.
 *
 * NOTE: There are some accepted limitations, so
 * that I don't spend a month perfecting a program
 * that is just supposed to be an exercise. This
 * program cannot handle contractions. It is also
 * case sensitive. This means "isn't" will count
 * as the word "isn", and "this" and "This" are
 * counted as two seperate words.
 */

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 100
#define MAXWORD 80

#ifdef _WIN32
#define STRDUP(word) _strdup(word)
// This function is because windows is pretty bad
// at handling EOF in the terminal
#define HAS_QUIT(q) strcmp("END", q)
#else
#define STRDUP(word) strdup(word)
#define HAS_QUIT(q) 0
#endif

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
struct line_list *add_line(struct line_list *,
                           int);
struct word_node *talloc();
char getch(void);
void ungetch(char);
int int_cmp(const void *, const void *);

char buf[BUF];
int bufp = 0;

int main(void) {
  struct word_node *tree = NULL;
  char word[MAXWORD];
  int line = 1;

  while (getword(word, MAXWORD - 1) != EOF &&
         HAS_QUIT(word) != 0) {
    if (word[0] == '\n') {
      line++;
      continue;
    } else if (isalpha(word[0]))
      tree = add_tree(tree, word, line);
  }

  print_tree(tree);
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
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = STRDUP(word);
    p->line_occurences = add_line(NULL, line);
    p->left = NULL;
    p->right = NULL;
  } else if ((cond = strcmp(p->word, word) == 0))
    p->line_occurences =
        add_line(p->line_occurences, line);
  else if (cond < 0)
    p->left = add_tree(p->left, word, line);
  else
    p->right = add_tree(p->right, word, line);

  return p;
}

struct line_list *add_line(struct line_list *list,
                           int line) {
  if (list == NULL) {
    list = malloc(sizeof(struct line_list));
    list->length = 1;
    list->list = malloc(sizeof(int));
    list->list[0] = line;
    return list;
  } else if (bsearch(&line, list->list,
                     list->length,
                     sizeof(list->list[0]),
                     int_cmp) != NULL)
    return list;

  list->length++;
  int *new_list =
      malloc(sizeof(int) * list->length);

  int *list_p = list->list;

  for (int i = 0; i < list->length; i++) {
    // If true, we don't need to insert yet
    if (*list_p < line && i + 1 < list->length)
      new_list[i] = *list_p++;
    else
      new_list[i] = line;
  }

  free(list->list);
  list->list = new_list;

  return list;
}

int int_cmp(const void *p1, const void *p2) {
  int *key = (int *)p1;
  int *comp = (int *)p2;

  if (*key < *comp)
    return -1;
  else if (*key > *comp)
    return 1;

  return 0;
}

void print_tree(struct word_node *tree) {
  if (tree != NULL) {
    print_tree(tree->left);
    printf("Word: %s\nLine occurences:",
           tree->word);
    for (int i = 0;
         i < tree->line_occurences->length; i++) {
      printf("%d",
             tree->line_occurences->list[i]);
      if (i + 1 < tree->line_occurences->length)
        printf(", ");
      else
        printf(" ");
    }
    printf("\n");
    print_tree(tree->right);
  }
}

struct word_node *talloc(void) {
  return malloc(sizeof(struct word_node));
}
