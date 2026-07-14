/*
   Exercise 1-24
   Write a program to check a C program for rudimentary syntax errors like unmatched parentheses,
   brackets, and braces. Don't forget about quotes, both single and double, escape sequences, and comments. 
   (This program is hard if you do it in full generality.)
*/

#include <stdio.h>

#define MAX_STR 1000
#define TRUE (1 == 1)
#define FALSE !TRUE

int get_str(char str[], int limit);

int main()
{
  char str[MAX_STR];
  int length, brackets, curly_brackets, parenthesis, single_quote, double_quote, line_comment, block_comment, line;

  line_comment = block_comment = FALSE;
  parenthesis = single_quote = double_quote = brackets = curly_brackets = line = 0;

  length = get_str(str, MAX_STR);

  for (int i = 0; i < length; i++)
  {
    if (line_comment == TRUE)
      if (str[i] == '\n')
        line_comment = FALSE;
    if (block_comment == TRUE)
      if (str[i] == '*' && str[i+1] == '/') {
        block_comment = FALSE;
        i++;
      }

    if (line_comment == FALSE && block_comment == FALSE) {
      if (str[i] == '(')
        parenthesis++;
      else if (str[i] == ')')
        parenthesis--;
      else if (str[i] == '[')
        brackets++;
      else if (str[i] == ']')
        brackets--;
      else if (str[i] == '{')
        curly_brackets++;
      else if (str[i] == '}')
        curly_brackets--;
      else if (str[i] == '"') {
        if (double_quote == 0)
          double_quote = 1;
        else 
          double_quote = 0;
      }
      else if (str[i] == '\'') {
        if (single_quote == 0)
          single_quote = 1;
        else
          single_quote = 0;
      }
      else if (str[i] == '\n') {
        if (double_quote > 0)
          printf("There is an unclosed double quote in line %d", line);
        else if (single_quote > 0)
          printf("There is an unclosed single quote in line %d", line);
      }
      else if (str[i] == '/') {
        if (str[i+1] == '/') {
          line_comment = TRUE;
          i++;
        }
        else if (str[i+1] == '*') {
          block_comment = TRUE;
          i++;
        }
      }
      
      if (str[i] == '\n')
        line++;
    }
  }

  if (parenthesis > 0)
    printf("Unclosed parenthesis detected\n");

  if (brackets > 0)
    printf("Unclosed brackets detected\n");

  if (curly_brackets > 0)
    printf("Unclosed curly brackets detected\n");

  if (single_quote > 0)
    printf("Unclosed single quote detected\n");

  if (double_quote > 0)
    printf("Unclosed double quote detected\n");
  
}

int get_str(char str[], int limit)
{
  int c, i;

  i = 0;

  while ((c = getchar()) != EOF && i < limit) {
    str[i] = c;
    i++;
  }
  return i;
}

