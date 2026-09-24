/* Exercise 7-4
 *
 * Write a private version of scanf analogous to
 * minprintf from the previous section.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int minscanf(char *input, char *fmt, ...) {
  int c;
  char *p, *start, *end;
  va_list *a;

  va_start(*a, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%')
      continue;

    start = p;
    while(isblank(*(start++)))
        ;

    end = start;

    while (!isblank(*(end++)))
        ;



    switch (*++p) {
      case 'd':

    }
  }


}
