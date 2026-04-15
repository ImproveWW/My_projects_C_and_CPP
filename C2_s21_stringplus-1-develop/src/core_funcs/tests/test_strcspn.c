/*Вычисляет длину начального сегмента str1,
который полностью состоит из символов, не входящих в str2.

*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str1[] = "aurol";
  const char str2[] = "verter";  // вторая строка (символы для поиска)
  size_t result = s21_strcspn(str1, str2);
  printf("Длина начального сегмента: %zu\n", result);
  return 0;
}
