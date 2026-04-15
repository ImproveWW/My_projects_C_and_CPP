#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = 0;
  int exp = s21_get_exp(value);
  (*result = value);
  int is_negative = getSign(value);
  if (exp <= 28) {
    result->bits[3] = 0;
    int remainder = 0;
    while (exp > 0) {
      del10(result);
      remainder = result->bits[0];
      exp--;
    }
    if (remainder && s21_get_exp(value)) {
      s21_decimal one = {{1, 0, 0, 0}};
      if (remainder >= 5) {
        set_scale(result, 0);
        setSign(result, 0);
        res = add_temp(*result, one, result);  // Увеличиваем на 1
      }
    }
    setScale(result, exp);
    setSign(result, is_negative);
    if (res != 0) res = 1;
  } else {
    res = 1;
  }
  return res;
}
