#include <stdio.h>

#define TRUE (1==1)
#define FALSE !TRUE
#define MAX_STRING 1000

int get_str(char str[], int limit);
int remove_comments(char with_comments[], char without_comments[]);

int main() {
  int block_comment, line_comment;
  char str[MAX_STRING];
  char without_comments[MAX_STRING];

  get_str(str, MAX_STRING);
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
  int in_block = FALSE;

  int i = 0;

  while (with_comments[i] != '\0') {
    if (with_comments[i] == '/') {
      if (with_comments[i+1] == '/') 
        line_comment = TRUE;
    }
  }
}
