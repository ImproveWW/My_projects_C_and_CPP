#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == NULL) {
    return NULL;
  }

  const unsigned char *byte = str;
  while (n > 0) {
    if (*byte == c) {
      return (void *)byte;
    }
    byte++;
    n--;
  }

  return NULL;
}
