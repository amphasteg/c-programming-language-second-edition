/*
   Exercise 3-1

   Our binary search makes two tests inside the
   loop, when one would suffice (at the price of
   more tests outside.) Write a version with only
   one test inside the loop and measure the
   difference in run-time.
*/

#include <stdio.h>

int binsearch(int x, int v[], int n);

 int main() {
   int v[] = {1, 2, 3, 4, 5};

   printf("%d\n", binsearch(3, v, 5));
}

int binsearch(int x, int v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low + high) / 2;
    if (x > v[mid])
      low = mid + 1;
    else
      high = mid - 1;
  }


  if (x == v[low])
    return low;

  return -1;
}
