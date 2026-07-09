/*
  Exercise 1-13
  Write a program to print a a histogram of the lengths
  of words in its input. It is easy to draw the histogram
  with the bars horizontal; a vertical orientation is more
  challenging.
*/

#include <stdio.h>

#define MAX_WORD 100 //Defines the maximum words that can be entered

int main() {
  int histogram[MAX_WORD];
  int c, letterCount, maxLetterCount, wordCount;

  wordCount = maxLetterCount = letterCount = 0;

  while ((c = getchar()) != EOF && wordCount < MAX_WORD) 
    if (letterCount > 0 && (c == ' ' || c == '\t' || c == '\n')) 
    {
      histogram[wordCount] = letterCount;
      wordCount++;

      if (letterCount > maxLetterCount)
        maxLetterCount = letterCount;

      letterCount = 0;
    }
    else
      letterCount++;

  //Prints histogram horizontally
  printf("Horizontal\n");

  for (int i = 0; i < wordCount; i++)
  {
   int letters = histogram[i];

    if (letters > 0)
     for (int l = 0; l < letters; l++)
       putchar('*');

   putchar('\n');
  }
  
  //Prints histogram vertically
  printf("Vertical\n");

  for (int l = maxLetterCount; l > 0; l--)
  {
    for (int w = 0; w < wordCount; w++)
      if (histogram[w] >= l)
        putchar('*');
      else
       putchar(' ');

    putchar('\n');
  }

}
