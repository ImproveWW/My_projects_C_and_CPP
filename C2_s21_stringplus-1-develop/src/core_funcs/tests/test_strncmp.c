/*Сравнивает не более первых n байтов str1 и str2.

*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str1[] = "halohalohalo";
  const char str2[] = "halohaloholal";
  int result = s21_strncmp(str1, str2, 10);
  printf("Результат сравнения: %d\n", result);
  return 0;
}
