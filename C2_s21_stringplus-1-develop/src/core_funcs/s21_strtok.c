#include <string.h>

#include "../s21_string.h"

static char *s21_strtok_save = NULL;

char *s21_strtok(char *str, const char *delim) {
  if (str == NULL) {
    str = s21_strtok_save;
  }
  if (str == NULL) {
    return NULL;
  }

  char *token_start = str;
  while (*str && strchr(delim, *str)) {
    str++;
  }
  if (*str == '\0') {
    s21_strtok_save = NULL;
    return NULL;
  }

  token_start = str;
  while (*str && !strchr(delim, *str)) {
    str++;
  }
  if (*str) {
    *str = '\0';
    s21_strtok_save = str + 1;
  } else {
    s21_strtok_save = NULL;
  }

  return token_start;
}
