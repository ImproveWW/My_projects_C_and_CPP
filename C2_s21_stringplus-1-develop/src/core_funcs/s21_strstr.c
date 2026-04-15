#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  if (!*needle) return (char *)haystack;
  for (; *haystack; haystack++) {
    if (*haystack == *needle) {
      const char *h, *n;
      for (h = haystack, n = needle; *h && *n; h++, n++) {
        if (*h != *n) break;
      }
      if (!*n) return (char *)haystack;
    }
  }
  return NULL;
}
