/*Добавляет строку, на которую указывает src, в конец строки,
на которую указывает dest, длиной до n символов.
*/

#include <stdio.h>

#include "../s21_string.h"

int main() {
  char dest[20] = "hi, lovely ";
  const char src[] = "piiiireeeee";
  s21_strncat(dest, src, 6);
  printf("Объединенная строка: %s\n", dest);
  return 0;
}
