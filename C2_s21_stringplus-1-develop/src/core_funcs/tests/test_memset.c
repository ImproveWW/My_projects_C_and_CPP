/*Копирует символ c (беззнаковый тип) в первые n символов строки,
на которую указывает аргумент str.*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  char str[15] = "dream_string";
  s21_memset(str, 'a', 4);
  printf("Измененная строка: %s\n", str);
  return 0;
}
