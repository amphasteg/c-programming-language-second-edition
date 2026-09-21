/*
 * Exercise 6-4
 *
 * Write a program that prints the distinct words
 * in its input sorted into decreasing order of
 * frequency of occurence. Precede each word by
 * its count.
 */

#include <_string.h>
#include <arm/types.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 100
#define LIM 100

struct word_tree {
  struct word *word;
  struct word_tree *left;
  struct word_tree *right;
};

struct word_list {
  struct word *word_list;
  int size;
};

struct word {
  char *word;
  int count;
};

int getword(char *, int);
char getch(void);
void ungetch(char);
void add_tree(struct word_tree **, char *word);
void print_tree(struct word_tree *);
void insert_item(struct word_tree *,
                 struct word_list **);

char buf[BUF];
int bufp = 0;

int main(void) {
  char word[LIM];
  struct word_tree *root = NULL;

  while (getword(word, LIM) != EOF && strcmp(word, "END") != 0) {
    if (isalpha(word[0]))
      add_tree(&root, word);
  }

  print_tree(root);
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

// This modifies the tree directly in place,
// without needing to return values. Similar to
// "pass by reference" in other languages.
void add_tree(struct word_tree **tree,
              char *word) {
  int cond;
  if (*tree == NULL) {
    *tree = malloc(sizeof(struct word_tree));
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->word = malloc(sizeof(struct word));
    (*tree)->word->word = strdup(word);
    (*tree)->word->count = 1;
  } else if ((cond = strcmp((*tree)->word->word,
                            word)) == 0)
    (*tree)->word->count++;
  else if (cond < 0)
    add_tree(&(*tree)->left, word);
  else
    add_tree(&(*tree)->right, word);
}

void print_tree(struct word_tree *tree) {
  if (tree == NULL) {
    printf("Print tree: tree is null\n");
    return;
  }

  struct word_list *list =
      malloc(sizeof(struct word_list));
  list->size = 0;

  insert_item(tree, &list);

  for (int i = 0; i < list->size; i++) {
    struct word item = list->word_list[i];

    printf("%d %s\n", item.count, item.word);
  }

  free(list);
}

//Also passes by reference, yippee!!
void insert_item(struct word_tree *node,
                 struct word_list **list) {
  if (*list == NULL || node == NULL) {
    return;
  }

  insert_item(node->left, &*list);
  struct word *new_list = malloc(
      sizeof(struct word) * ((*list)->size + 1));
  int i = 0;
  while (i < (*list)->size &&
         node->word->count <
             ((*list)->word_list + i)->count)
    i++;

  (*list)->size++;

  memcpy(new_list, (*list)->word_list,
         sizeof(struct word) * i);

  new_list[i++] = *node->word;

  memcpy(new_list + i, (*list)->word_list,
         sizeof(struct word) * ((*list)->size - i));

  free((*list)->word_list);
  (*list)->word_list = new_list;
  insert_item(node->right, &*list);
}
