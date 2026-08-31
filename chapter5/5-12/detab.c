/*
 * Exercise 5-11
 *
 * Modify the program entab and detab (written
 * as exercises in Chapter 1) to accept a list
 * of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
 */
#include <stdio.h>
#include <stdlib.h>

#define TAB_SPACE 8

int main(int argc, char *argv[]) {
  int c, count;
  int tab_spaces[argc - 1];
  int *tab_pointer = tab_spaces;

  count = 0;

  while (--argc > 0) {
    int tab = atoi(*++argv);
    *tab_pointer++ = tab ? tab : TAB_SPACE;
    --argc;
  }

  // Reset tab pointer back to start of array
  tab_pointer = tab_spaces;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      count = 0;
      tab_pointer++;
      putchar(c);
    } else if (c == '\t') {
      int spaces = *tab_pointer - (count % *tab_pointer);
      for (int i = 0; i < spaces; i++)
        putchar(' ');
    } else {
      count++;
      putchar(c);
    }
  }
}
