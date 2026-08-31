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
  int c, count, spaces, tabs, current_tab_space;
  int tab_spaces[argc - 1];
  int *tab_pointer = tab_spaces;

  spaces = tabs = 0;
  count = 0;

  while (--argc > 0) {
    int tab = atoi(*++argv);
    *tab_pointer++ = tab ? tab : TAB_SPACE;
    --argc;
  }

  // Reset tab pointer back to start of array
  tab_pointer = tab_spaces;

  while ((c = getchar() != EOF)) {
    if (c == ' ') {
      if ((count % *tab_pointer) != 0)
        spaces++;
      else {
        spaces = 0;
        tabs++;
      }
    } else {
      for (; tabs > 0; tabs--)
        putchar('\t');

      if (c == '\t')
        spaces = 0;
      else
        for (; spaces > 0; spaces--)
          putchar(' ');

      putchar(c);

      if (c == '\n') {
        tab_pointer++;
        count = 0;
      } else if (c == '\t')
        count = count + (*tab_pointer - (count - 1) % *tab_pointer) - 1;
    }
  }
}
