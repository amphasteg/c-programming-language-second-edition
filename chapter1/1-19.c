#include <stddef.h>
#include <stdio.h>

#define MAX_LINE 1000

int get_line(char line[], int max);
void reverse_copy(char to[], char from[]);
int length(char line[]);

int main() {
  int len, max;

  char line[MAX_LINE];
  char reversed[MAX_LINE];

  while ((len = get_line(line, MAX_LINE)) > 0) {
    reverse_copy(reversed, line);
    printf("%s\n", reversed);
  }
}

int get_line(char line[], int max) {
  int c, i;

  for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    line[i] = c;

  line[i] = '\0';
  return i--;
}

void reverse_copy(char to[], char from[]) {
  int size = length(from);
  int r = 0;

  for (int i = size-1; i >= 0; i--) { 
    to[r] = from[i];
    r++;
  }
}

int length(char line[])
{
  int i;

  for (i = 0; line[i] != '\0'; i++)
    ;

  return i;
}
