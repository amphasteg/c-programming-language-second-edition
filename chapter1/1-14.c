/*
   Exercise 1-14
   Write a program to print a histogram of the frequencies of different characters
   in its input.
 */

#include <stdio.h>

/* Note: At this point, the book has not gone over booleans, hence, they are not included in this program.
   If you feel comfortable with doing so, modify this program to use a bool instead of the FOUND macro.
*/
#define FOUND 200

int main()
{
  int characterIndex, character, highestFrequency;
  int charactersUsed[100];
  int characterFrequency[100];

  characterIndex = 0;
  highestFrequency = 0;

  //Gathers input, records character frequencies
  while ((character = getchar()) != EOF) 
  {
    int i, found;

    i = found = 0;

    while (i < characterIndex)
    {
      if (character == charactersUsed[i])
      {
        characterFrequency[i]++;
        found = FOUND;

        if (characterFrequency[i] > highestFrequency)
          highestFrequency = characterFrequency[i];
      }
      i++;
    }

    if (found != 200)
      {
        charactersUsed[characterIndex] = character;
        characterFrequency[characterIndex] = 1;
        characterIndex++;
      }
  }


  for (int i = 0; i < characterIndex; i++)
  {
    printf("Character code ");

    if (charactersUsed[i] == '\n')
      printf("return");
    else if (charactersUsed[i] == '\t')
      printf("tab");
    else if (charactersUsed[i] == '\b')
      printf("backspace");
    else if (charactersUsed[i] == ' ')
      printf("' '");
    else 
      putchar(charactersUsed[i]);

    printf(" was used %d times.\n", characterFrequency[i]);
    printf("The highest occurrence was %d\n", highestFrequency);
  }

  printf("\n\n");

  //Prints horizontal histogram
  printf("Horizontal\n");

  for (int i = 0; i < characterIndex; i++)
  {
    for (int f = 0; f < characterFrequency[i]; f++)
      putchar('*');
    putchar('\n');
  }
  
  
  //Prints vertical histogram
  printf("\nVertical\n");

  for (int f = highestFrequency; f >= 0; f--)
  {
    for (int i = 0; i < characterIndex; i++)
    {
      if (characterFrequency[i] > f)
        putchar('*');
      else
        putchar(' ');
    }

    putchar('\n');
  }

}
