#include <stdio.h>

#define TAB_SPACE 8 

int main() {
  int c, count, spaces, tabs;

  spaces = tabs = 0;

  count = 0;

  while((c = getchar()) != EOF) {
     if (c == ' ')
     {
       if ((count % TAB_SPACE) != 0)
         spaces++;
       else {
         spaces = 0;
         tabs++;
       }
     }
     else {
       for (; tabs > 0; tabs--)
         putchar('\t');

       if (c == '\t')
         spaces = 0;
       else 
         for (; spaces > 0; spaces--)
           putchar(' ');

       putchar(c);

       if (c == '\n')
         count = 0;
       else if (c == '\t')
         count = count + (TAB_SPACE - (count - 1) % TAB_SPACE) - 1;
     }
  }
}
