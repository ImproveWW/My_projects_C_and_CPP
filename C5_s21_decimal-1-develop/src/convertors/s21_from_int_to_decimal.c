#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;  // Переменная для кода результата

  if (dst == NULL) {
    result = 1;  // Устанавливаем код ошибки
  } else {
    memset(dst, 0, sizeof(s21_decimal));  // Обнуляем dst
    int sign = src < 0;                   // Определяем знак
    if (sign) {
      src *= -1;  // Превращаем в положительное значение
    }
    dst->bits[0] = src;  // Записываем значение в dst

    if (sign) {
      set_sign(dst);  // Устанавливаем знак, если он отрицательный
    }
  }

  return result;  // Возвращаем код результата
}