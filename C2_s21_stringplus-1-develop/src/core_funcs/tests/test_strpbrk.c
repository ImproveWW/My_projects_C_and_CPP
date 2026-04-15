/*Находит первый символ в строке str1, который соответствует любому символу,
 * указанному в str2.
 */

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str1[] = "sleep_pleaze";
  const char str2[] = "dont_think_so";
  char *result = s21_strpbrk(str1, str2);
  if (result != NULL) {
    printf("Первый совпадающий символ: %c\n", *result);
  } else {
    printf("Совпадающие символы не найдены\n");
  }
  return 0;
}
