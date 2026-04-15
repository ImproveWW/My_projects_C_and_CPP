#include <ctype.h>

#include "../s21_string.h"

void *s21_to_lower(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  size_t str_len = s21_strlen(str) + 1;
  char *lower_str = (char *)malloc(str_len * sizeof(char));
  if (lower_str == s21_NULL) {
    return s21_NULL;
  }

  for (size_t i = 0; i < str_len - 1; i++) {
    lower_str[i] = tolower((unsigned char)str[i]);
  }

  lower_str[str_len - 1] = '\0';

  char *result = lower_str;
  lower_str = NULL;
  free(lower_str);

  return result;
}
