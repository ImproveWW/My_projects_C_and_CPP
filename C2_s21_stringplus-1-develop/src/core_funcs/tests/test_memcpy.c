/*Копирует n символов из src в dest.*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  char dest[10];
  const char src[] = ".l,kmjn";
  s21_memcpy(dest, src, 10);
  printf("Скопированная строка: %s\n", dest);
  return 0;
}
