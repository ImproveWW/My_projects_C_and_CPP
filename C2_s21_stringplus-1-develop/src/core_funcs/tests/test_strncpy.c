/*Копирует до n символов из строки, на которую указывает src, в dest.
 */

#include <stdio.h>

#include "../s21_string.h"

int main() {
  char dest[10];
  const char src[] = "l1@olooxdcfghuji";
  s21_strncpy(dest, src, 7);
  printf("Скопированная строка: %s\n", dest);
  return 0;
}
