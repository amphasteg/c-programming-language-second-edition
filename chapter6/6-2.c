/*
 * Exercise 6-2
 *
 * Write a program that reads a C program and
 * prints in alphabetical order each group of
 * varaible names that are identical in the first
 * 6 characters, but different somewhere
 * thereafter. Don't cound words within strings
 * and comments. Make 6 a parameter that can be
 * set from the command line.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct word {
  char *word;
  struct word *left;
  struct word *right;
};

struct first_chars {
  char *first_chars;
  struct word *root_word;
  struct first_chars *left;
  struct first_chars *right;
};

// Types that will always come before a variable
// name, and if not, then it is not a var.
// e.g. 'int x' is a var,
// but func(int) is not.
const char *types[] = {"int", "char", "float",
                       "double"};

// Certain, non-alphanumeric characters in C are
// allowed to be in the names of variables
const char allowed_chars[] = {'_', '-'};

// Number of identical chars. Defaults to 6
unsigned int n_chars = 6;

int check_args(int, char **);
int getword(char *, int);
int compare_type(char *, const char *[], int);
struct first_chars *
add_new_word(struct first_chars *p,
             char *full_word);
void print_tree(struct first_chars *);

int main(int argc, char *argv[]) {
  struct first_chars *tree;

  if (check_args(argc, argv) == -1)
    return -1;

  char word[MAXWORD];

  while (getword(word, MAXWORD) != '\n') {
    if (compare_type(word, types, 4) == 0 &&
        getword(word, MAXWORD) != EOF) {
      tree = add_new_word(tree, word);
    }
  }

  print_tree(tree);
  return 0;
}

// Verifies arguments are formatted correctly
// and sets n if they are
int check_args(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Too many arguments : %d. The only "
           "argument for this program is --n; "
           "where n is the number of identical "
           "characters to look for.",
           argc);
    return -1;
  } else if (argc == 2) {
    if (*argv[1] != '-' &&
        *(argv[1] + 1) != '-') {
      printf("Optional argument must be "
             "preceeded by \"--\"");
      return -1;
    }

    // Remove the '--'
    char *char_num = argv[1] + 2;

    // Assign and check if is a number
    int temp_num = atoi(char_num);

    if (temp_num > 0)
      n_chars = temp_num;
    else {
      printf("The argument provided is not a "
             "number: %s",
             char_num);
      return -1;
    }
  }

  return 0;
}

// This modified getword function will return
// everything has spaces inbetween it; similar
// to something like Vim
int getword(char *word, int lim) {
  int c, in_str_const, getch(void);
  void ungetch(int);

  char *w = word;

  while (isspace(c = getch()))
    if (c == '\n') {
      *w = c;
      return word[0];
    }

  if (c != EOF)
    *w++ = c;

  for (; --lim > 0; w++)
    if (!isalnum(*w = getch()) &&
        strchr(allowed_chars, *w) == NULL) {
      ungetch(*w);
      break;
    }

  *w = '\0';
  return word[0];
}

// Compares word to given list of types
int compare_type(char *word, const char *types[],
                 int type_size) {
  for (int i = 0; i < type_size; i++)
    if (strcmp(word, types[i]) == 0)
      return 0;

  return -1;
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

struct first_chars *first_char_alloc(void);
struct word *word_alloc(void);
char *strndupl(char *, unsigned int);
struct word *add_word(struct word *p,
                      char *full_word);

struct first_chars *
add_new_word(struct first_chars *p,
             char *full_word) {
  if (p == NULL) {
    p = first_char_alloc();
    p->first_chars = strndupl(full_word, n_chars);
    p->root_word = NULL;
    p->left = p->right = NULL;
    p->root_word =
        add_word(p->root_word, full_word);
  } else if (strncmp(p->first_chars, full_word,
                     n_chars) < 0)
    p->left = add_new_word(p->left, full_word);
  else
    p->right = add_new_word(p->right, full_word);

  return p;
}

struct word *add_word(struct word *p,
                      char *full_word) {
  int cond;
  if (p == NULL) {
    p = word_alloc();
    p->word =
        strndupl(full_word, strlen(full_word));
    p->left = p->right = NULL;
  } else if ((cond = strcmp(full_word, p->word)) <
             0)
    add_word(p->left, full_word);
  else
    add_word(p->right, full_word);

  return p;
}

char *strndupl(char *s, unsigned int size) {
  char *p = (char *)malloc(size + 1);

  if (p != NULL)
    strncpy(p, s, size + 1);

  return p;
}

struct first_chars *first_char_alloc(void) {
  return (struct first_chars *)malloc(
      sizeof(struct first_chars));
}

struct word *word_alloc(void) {
  return (struct word *)malloc(
      sizeof(struct word));
}

void print_words(struct word *p);

void print_tree(struct first_chars *p) {
  if (p == NULL)
    return;

  print_tree(p->left);
  printf("\n");
  print_words(p->root_word);
  printf("\n");
  print_tree(p->right);
}

void print_words(struct word *p) {
  if (p == NULL)
    return;

  print_words(p->left);
  printf("%s\n", p->word);
  print_words(p->right);
}
