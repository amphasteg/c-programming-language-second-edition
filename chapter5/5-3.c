/*
   Exercise 5-3

   Write a pointer version of the function strcat
   that was shown in Chapter2: strcat(s,t) copies
   the string t to to the end of s.
*/

#include <stdio.h>

//This function is being renamed to scat to avoid
//standard library conflicts.
void scat(char* s, char* t);

int main(void) {
  char s[] = "This is a string";
  char t[] = ", but it wasn't finished!";

  scat(s, t);

  printf("%s\n", s);
}

void scat(char* s, char* t) {
  for ( ; *s; s++)
    ;

  while ((*s++ = *t++)) 
    ;

  *s = '\0';
}
  
