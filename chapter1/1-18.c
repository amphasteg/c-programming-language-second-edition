#include <stddef.h>
#include <stdio.h>

#define MAX_LINE 1000

int getLine(char line[], int limit);
int append(char to[], char from[], int toLen, int fromLen);
void trim(char s[], int len);

int main(void) {
  char input[MAX_LINE];
  char finalOutput[MAX_LINE];

  int totalLength, lineLength;

  lineLength = totalLength = 0;

  while ((lineLength = getLine(input, MAX_LINE - totalLength)) > 0)
    totalLength = append(finalOutput, input, totalLength, lineLength);

  trim(finalOutput, totalLength);

  printf("%s", finalOutput);
}

//Takes two arrays and their lengths, appends one to the other, and returns the length of the new array.
int append(char to[], char from[], int to_len, int from_len) {
  int new_len = to_len;

  if (MAX_LINE - to_len < from_len) 
    return to_len;

  for (int i = 0; i < from_len; i++) {
    to[new_len] = from[i];
    new_len++;
  }

  return new_len;
}

int getLine(char line[], int limit) {
  int c, i;

  for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }

  line[i] = '\0';

  return i--;
}

void trim(char s[], int len) {
  int last_char = 0;

  for (int i = 0; i < len; i++)
    if (s[i] != '\n' && s[i] != ' ' && s[i] != '\t' && s[i] != EOF)
      last_char = i;

  for (int i = last_char + 1; i < MAX_LINE; i++)
    s[i] = '\0';
}
