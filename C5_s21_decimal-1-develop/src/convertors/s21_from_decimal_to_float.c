#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_code = 0;  // Код возврата, 0 - без ошибок
  if (dst == NULL) {
    result_code = 1;  // Ошибка: указатель на результат равен NULL
  } else {
    int sign = getSign(src);
    int power = s21_get_power(src);
    long double result = 0;

    for (int i = 0; i < 96; i++) {  // Переводим в десятичную систему
      result += pow(2, i) * getBit(src, i);
    }

    while (power > 0) {  // Отделяем дробную часть
      result /= 10.0;
      power--;
    }

    if (sign) {
      result *= -1.0;  // Учитываем знак
    }

    *dst = result;  // Записываем результат
  }

  return result_code;  // Возвращаем код результата
}
