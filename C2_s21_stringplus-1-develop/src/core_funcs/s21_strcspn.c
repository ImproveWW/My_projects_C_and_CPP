#include "../s21_string.h"

size_t s21_strcspn(const char *str1, const char *str2) {
  const char *s = str1;

  while (*s) {
    for (const char *p = str2; *p; p++) {
      if (*s == *p) {
        return s - str1;
      }
    }
    s++;
  }
  return s - str1;
}
