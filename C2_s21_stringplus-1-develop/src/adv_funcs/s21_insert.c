#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == NULL || str == NULL) {
    return NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);

  if (start_index > src_len) {
    return NULL;
  }

  s21_size_t new_len = src_len + str_len;
  char *new_str = (char *)malloc((new_len + 1) * sizeof(char));
  if (new_str == NULL) {
    return NULL;
  }

  s21_memcpy(new_str, src, start_index);

  s21_memcpy(new_str + start_index, str, str_len);

  s21_memcpy(new_str + start_index + str_len, src + start_index,
             src_len - start_index);

  new_str[new_len] = '\0';

  return new_str;
}
