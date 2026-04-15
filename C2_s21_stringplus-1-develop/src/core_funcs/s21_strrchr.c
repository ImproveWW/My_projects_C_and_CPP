#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char k = c;
  char *res = NULL;
  for (; *str != '\0'; str++) {
    if (*str == k) {
      res = (char *)str;
    }
  }
  if (res == NULL) {
    res = (char *)str;
  }
  return *res == c ? (char *)res : NULL;
}
