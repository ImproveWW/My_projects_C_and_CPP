/*Вычисляет длину строки str, не включая завершающий нулевой символ.

*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str[] = "06:40AM";
  size_t len = s21_strlen(str);
  printf("Длина строки: %zu\n", len);
  return 0;
}
