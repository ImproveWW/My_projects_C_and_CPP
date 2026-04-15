/*Разбивает строку str на ряд токенов, разделенных delim.
 */

#include <stdio.h>

#include "../s21_string.h"

int main() {
  char str[] = "well here we go to alkoponedel'nic";
  const char delim[] = " ";  // разделитель
  char *token = s21_strtok(str, delim);

  while (token != NULL) {
    printf("Найден токен: %s\n", token);  // вывод токена
    token = s21_strtok(NULL, delim);  // последующие вызовы s21_strtok
  }

  return 0;
}
