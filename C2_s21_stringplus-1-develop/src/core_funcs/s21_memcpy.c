#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  if (dest == NULL || src == NULL) {
    return NULL;
  }

  if (n == 0) {
    return dest;
  }

  for (s21_size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }

  return dest;
}
