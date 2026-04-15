/*Сравнивает первые n байтов str1 и str2.*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str1[] = "rertetetrt";
  const char str2[] = "red";
  int result = s21_memcmp(str1, str2, 3);
  printf("Результат сравнения: %d\n", result);
}
