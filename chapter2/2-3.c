/*
  Exercise 2-3
  Write a function htoi(s), which converts a string of hexadecimal digits
  (including an options 0x or 0X) into its equivilant integer value.
  The allowed digits are 0 throught 9, a through f, and A through F.
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#define LIMIT 1000

int get_str(char str[], int limit);
int htoi(char hex[]); 

int main() {
  char str[LIMIT];
  int decimal;

  get_str(str, LIMIT);

  decimal = htoi(str);
  
  printf("%d", decimal);
}

int get_str(char string[], int limit) {
  int c, i;

  i = 0;

  while ((c = getchar()) != EOF && c != '\n' && i < limit) {
   string[i] = c; 
   
   i++;
  }

  string[i] = '\0';

  return i;
}

int htoi(char hex[]) {
  int hex_total = 0;
  int length = strlen(hex);

  for (int i = length; i >= 0; i--) {
    if (hex[i] >= '0' && hex[i] <= '9') {
      int integer = hex[i] - '0';
      hex_total += integer * pow(16, i);
    }
    else if (hex[i] >= 'A' && hex[i] <= 'F') {
      int integer = hex[i] - 'A' + 10;
      hex_total += integer * pow(16, i);
    }
    else if (hex[i] >= 'a' && hex[i] <= 'f') {
      int integer = hex[i] - 'a';
      hex_total += integer * pow(16, i);
    }

    printf("%d\n", hex_total);
  }

  return hex_total;
}
