/*
 * Exercise 7-9
 *
 * Functions like isupper can be implemented to
 * save space or to save time. Explore both
 * possibilities.
 */

int my_isupper(char c) {
  return (c >= 'A' && c <= 'Z') ? 0 : 1;
}
