/*
 * Exercise 5-9
 *
 * Rewrite the routines day_of_year and month_day
 * with pointers instad of indexing
*/
#include <stdio.h>

static char yeardays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leapdays[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char* daytab[2]= {yeardays, leapdays};

int day_of_year(int year, int month, int day) {
  if (year < 1 || month < 1 || day < 1) {
    printf("Error: a year, month, and day must "
           "not be 0.\nYear: %d\n"
           "Month: %d\nDay: %d\n",
           year, month, day);
    return -1;
  }

  int i, leap;
  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; i < month; i++)
    day += *(daytab+leap)[i];
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap;
  
  if (year < 1 || yearday < 1) {
    printf("Error: Year and year day must not "
        "be 0.\nYear: %d\n Yearday: %d\n",
        year, yearday);
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for (i = 1; yearday > *(daytab+leap)[i]; i++)
    yearday -= *(daytab+leap)[i];
  *pmonth = i;
  *pday = yearday;
}
