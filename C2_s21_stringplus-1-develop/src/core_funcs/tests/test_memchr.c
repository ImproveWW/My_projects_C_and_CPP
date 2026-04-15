/*Выполняет поиск первого вхождения символа c (беззнаковый тип)
в первых n байтах строки, на которую указывает аргумент str.*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  const char str[] = "tererey";
  char c = 'y';
  char *result = s21_memchr(str, c, sizeof(str));
  if (result != NULL) {
    printf("Найден символ '%c' на позиции: %ld\n", c, result - str);
  } else {
    printf("Символ '%c' не найден\n", c);
  }
  return 0;
}
