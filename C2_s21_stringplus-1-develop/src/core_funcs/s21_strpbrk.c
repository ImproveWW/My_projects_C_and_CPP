#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  while (*str1) {
    for (const char *p = str2; *p; p++) {
      if (*str1 == *p) {
        return (char *)str1;
      }
    }
    str1++;
  }
  return NULL;
}
