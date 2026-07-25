/*
   Exercise 3-2

   Write a fucntion escape(s, t) that converts
   characters like newline and tab into visible
   escape sequences like \n and \t as it copies
   the string from t to s. Use a switch. Write
   a function for the other direction as well,
   converting escape sequences into the real 
   characters.
*/

#include <stdio.h>
#define LEN 30

void escape(char s[], char t[]);
void inv_escape(char t[], char s[]);
int length(char s[]);

int main() {
  //For the sake of brevity, I will only convert these characters,
  //excluding the null char
  char escapes[] = {'\n', '\t', '\b', '\r', '\0'};
  char converted[LEN];

  escape(converted, escapes);
  printf("%s\n", converted);

  /*We could just convert the output of what
  we already converted, however, I am 
  choosing to do it this way to demonstrate
  more clearly.*/
  char written_escapes[] = {'\\', 'n', 
    '\\', 't', '\\', 'b', '\\', 'r', '\0'};
  char converted_escapes[LEN];
  inv_escape(converted_escapes, written_escapes);
  //This does not print much
  printf("%s", converted_escapes);
}

void escape(char s[], char t[]) {
  int len = length(t); 
  int converted_index = 0;

  for (int i = 0; i < len; i++)
  {
    switch (t[i]) {
      case '\n':
       s[converted_index] = '\\';
       s[converted_index+1] = 'n';
       converted_index += 2;
       break;
      case '\t':
       s[converted_index] = '\\';
       s[converted_index+1] = 't';
       converted_index += 2;
       break;
      case '\b':
       s[converted_index] = '\\';
       s[converted_index+1] = 'b';
       converted_index += 2;
       break;
      case '\r':
       s[converted_index] = '\\';
       s[converted_index+1] = 'r';
       converted_index += 2;
       break;
    }
  }
  s[converted_index] = '\0';
}

void inv_escape(char t[], char s[]) {
  int len = length(s);
  int escape_index = 0;

  for (int i = 0; i < len; i++) {
    if (s[i] == '\\') {
      switch (s[i+1]) {
        case 'n':
          t[escape_index] = '\n';
          escape_index++;
          i++;
          break;
        case 't':
          t[escape_index] = '\t';
          escape_index++;
          i++;
          break;
        case 'b':
          t[escape_index] = '\b';
          escape_index++;
          i++;
          break;
        case 'r':
          t[escape_index] = '\r';
          escape_index++;
          i++;
          break;
      }
    }
  }
  t[escape_index] ='\0';
}

int length(char s[]) {
  int len;
  for (len = 0; s[len] != '\0'; len++)
    ;
  return len + 1;
}
