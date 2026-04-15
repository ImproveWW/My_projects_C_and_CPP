#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int exp = s21_get_exp(value);
  int negative = getSign(value);
  result->bits[3] = 0;

  if (exp <= 28) {
    int remainder = 0;
    (*result) = value;
    while (exp > 0) {
      del10(result);
      remainder = result->bits[0];
      exp--;
    }

    // Если число отрицательное и дробная часть была отброшена
    if (negative && remainder && s21_get_exp(value)) {
      setScale(result, 0);
      setSign(result, 0);
      s21_decimal one = {{1, 0, 0, 0}};
      res = add_temp(*result, one, result);  // Уменьшаем на 1
    }
    setScale(result, exp);
    setSign(result, negative);
    if (res != 0) res = 1;
  } else {
    res = 1;
  }
  return res;
}

int s21_get_exp(s21_decimal value) {
  uint32_t exp = (value.bits[3] & 0x00FF0000) >> 16;
  return exp;
}