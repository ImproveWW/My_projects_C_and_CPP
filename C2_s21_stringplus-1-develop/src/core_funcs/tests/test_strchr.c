/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке,
 на которую указывает аргумент str.
*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str[] = "hellojzsdyv";
  char c = 'v';
  char *result = s21_strchr(str, c);
  if (result != NULL) {
    printf("Найден символ '%c' на позиции: %ld\n", c, result - str);
  } else {
    printf("Символ '%c' не найден\n", c);
  }
  return 0;
}
