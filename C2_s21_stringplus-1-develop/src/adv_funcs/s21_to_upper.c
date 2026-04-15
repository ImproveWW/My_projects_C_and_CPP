#include <ctype.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) {
    return s21_NULL;
  }

  char *upper_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  if (upper_str == s21_NULL) {
    return s21_NULL;
  }
  for (int i = 0; str[i] != '\0'; i++) {
    upper_str[i] = toupper((unsigned char)str[i]);
  }
  upper_str[s21_strlen(str)] = '\0';

  return upper_str;
}