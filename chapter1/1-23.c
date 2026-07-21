/*
   Exercise 1-23
   Write a program to remove all comments from a C program.
   Don't forget to handle quoted strings and character constants properly. C
   comments don't nest.
*/
#include <stdio.h>

#define TRUE (1 == 1)
#define FALSE !TRUE
#define MAX_STRING 1000

int get_str(char str[], int limit);
int remove_comments(char with_comments[], char without_comments[]);

int main() {
  char str[MAX_STRING];
  char without_comments[MAX_STRING];

  get_str(str, MAX_STRING);
  
  remove_comments(str, without_comments);

  printf("%s", without_comments);
}

int get_str(char str[], int limit) {
  int c;
  int i = 0;

  while (i < limit && (c = getchar()) != EOF) {
    str[i] = c;
    i++;
  }

  str[i] = '\0';

  return i;
}

int remove_comments(char with_comments[], char without_comments[]) {
  int block_comment = FALSE;
  int line_comment = FALSE;
  int i = 0;
  int c = 0;

  while (with_comments[i] != '\0') {
    printf("i: %d, c: %d\n", i, c);
    if (block_comment == TRUE && with_comments[i] == '*' &&
        with_comments[i + 1] == '/') {
      block_comment = FALSE;
      i += 2;
    }
    else if (line_comment == TRUE && with_comments[i] == '\n') {
      line_comment = FALSE;
      without_comments[c] = with_comments[i];
      i++;
      c++;
    }
    else if (with_comments[i] == '/') {
      if (with_comments[i + 1] == '/') {
        line_comment = TRUE;
        i += 2;
      } 
      else if (with_comments[i + 1] == '*') {
        block_comment = TRUE;
        i += 2;
      }
      else {
        without_comments[c] = with_comments[i];
        i++;
        c++;
      }
    }
    else if (line_comment == FALSE && block_comment == FALSE) {
      without_comments[c] = with_comments[i];
      i++;
      c++;
    }
    else
      i++;
  }
  
  return c;
}
