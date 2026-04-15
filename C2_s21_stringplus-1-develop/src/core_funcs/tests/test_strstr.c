/*Находит первое вхождение всей строки needle (не включая завершающий нулевой
символ), которая появляется в строке haystack.
*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char haystack[] = "hello world";  // исходная строка (в которой ищем)
  const char needle[] = "world";  // подстрока для поиска
  char *result = s21_strstr(haystack, needle);
  if (result != NULL) {
    printf("Подстрока найдена на позиции: %ld\n", result - haystack);
  } else {
    printf("Подстрока не найдена\n");
  }
  return 0;
}
