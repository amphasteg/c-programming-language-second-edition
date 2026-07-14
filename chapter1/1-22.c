#include <stdio.h>

#define CUTOFF 12
#define MIN 8

int main() {
  int count, c;

  count = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      putchar(c);
      count = 0;
    }
    else if (MIN < count && (c == ' ' || c == '\t')) {
      putchar('\n');
      count = 0;
    }
    else if (count > CUTOFF)
    {
      putchar('-');
      putchar('\n');
      putchar(c);
      count = 0;
    }
    else {
      putchar(c);
    }
    count++;
  }
}
