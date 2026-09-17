/*
 * Exercise 6-3
 *
 * Write a cross-referencer that prints a list of
 * all words in a document and for each word, a
 * list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so
 * on.
 */

#include <stdlib.h>
#include <stdio.h>

#define BUF 100

struct word_node {
  int *line_occurences;
  char *word;
  struct word_node* left;
  struct word_node* right;
};

const char* noise_words[] = {"the", "and", "that", "it", "to", "at", "it" };

int is_noise_word(char *);
struct word_node* add_node(struct word_node *, char*, int);
void print_tree(struct word_node*);
char* getword(void);

char getch(void);
void ungetch(char);

char buf[BUF];
int bufp = 0;

int main(void) {
  struct word_node *tree;

}
