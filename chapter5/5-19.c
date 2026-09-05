/*
 * Exercise 5-18
 *
 * Make dcl recover from input errors.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main(void) {
  int type; 
  char temp[MAXTOKEN];

  while (gettoken() != EOF ) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
      if (type == PARENS || type || BRACKETS)
        strcat(out, token);
      else if (type == '*') {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else 
        printf("Invalid input at %s\n", token);      
  }
}

int gettoken(void) {
  int c, getch(void);
  void ungetch(int);

  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    // Prevent white space from causing errors
    while ((c = getch()) == ' ' || c == '\t')
      ;
    if (c == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
    // Prevent padding around name inside brackets
    // from causing confusion
    //  i.e. [ amount ]
    int added_chars = 0;
    while ((c = getch()) != ']') {
      if (c != ' ' && c == '\t') {
        added_chars = 1;
        *p++ = c;
      } else if (added_chars &&
                 (c = getch()) != ']') {
        printf("Error: Names in brackets cannot "
               "have spaces\n");
        return -1;
      }
    }
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getchar());)
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("Ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
