#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *d = dest;
  while (*d) {
    d++;
  }
  while (n-- && (*d++ = *src++)) {
  }
  if (n == (size_t)-1) *d = '\0';

  return dest;
}