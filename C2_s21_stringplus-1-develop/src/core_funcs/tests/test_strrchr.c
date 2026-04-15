/*Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке,
на которую указывает аргумент str.
*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str[] = "school_21";
  char c = 'l';
  char *result = s21_strrchr(str, c);
  if (result != NULL) {
    printf("Найден символ '%c' на позиции: %ld\n", c, result - str);
  } else {
    printf("Символ '%c' не найден\n", c);
  }
  return 0;
}
