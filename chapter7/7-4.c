/* Exercise 7-4
 *
 * Write a private version of scanf analogous to
 * minprintf from the previous section.
 */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

int minsscanf(char *fmt, ...) {
  int consumed, result;
  int c;
  char *p;
  va_list a;

  va_start(a, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%')
      continue;

    switch (*++p) {
      case 'd':
        result = scanf("%d", va_arg(a, int));
        break;
      case 'f':
        result = scanf("%f", va_arg(a, double));
        break;
      case 's':
        result = scanf("%s", va_arg(a, char*));
        break;
      case 'c':
        result = scanf("%c", va_arg(a, int));
        break;
      default:
        result = 0;
    }

    if (result != EOF && result != 0)
      consumed += result;
    else
     return result;
  }

  return consumed;
}
