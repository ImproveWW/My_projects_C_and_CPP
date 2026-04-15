#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *p = dest;
  s21_size_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    p[i] = src[i];
  }

  for (; i < n; i++) {
    p[i] = '\0';
  }

  return dest;
}
