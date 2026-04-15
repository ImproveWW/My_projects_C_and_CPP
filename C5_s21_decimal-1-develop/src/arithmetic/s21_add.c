#include "../s21_decimal.h"

#define DECIMAL_1 ((s21_decimal){{0x9999999A, 0x99999999, 0x19999999, 0}})

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_value_1 = getSign(value_1);
  int sign_value_2 = getSign(value_2);
  int error = 0;
  s21_decimal res = {0};
  if (getScale(value_1) != getScale(value_2))
    copmare_positive(&value_1, &value_2);
  set_scale(&res, getScale(value_2));
  if (sign_value_1 && sign_value_2) {
    s21_negate(value_1, &value_1);
    s21_negate(value_2, &value_2);
    error = add_temp(value_1, value_2, &res);
    s21_negate(res, &res);
  } else if (!sign_value_1 && !sign_value_2) {
    error = add_temp(value_1, value_2, &res);
    setSign(&res, 0);
  } else {
    if (sign_value_1) {
      s21_negate(value_1, &value_1);
      error = s21_sub(value_2, value_1, &res);
    } else {
      s21_negate(value_2, &value_2);
      error = s21_sub(value_1, value_2, &res);
    }
  }
  set_scale(&res, getScale(value_1));
  int sign = getSign(res);
  if (error && getScale(res) == 0 && sign) {
    s21_nullify(&res);
    error = 2;
  } else if (error && getScale(res) == 0 && !sign) {
    s21_nullify(&res);
    error = 1;
  } else if (error && getScale(res) != 0) {
    int new = getScale(res) - 1;
    bank(&res);
    add_temp(res, DECIMAL_1, &res);
    setScale(&res, new);
    error = 0;
  }
  if (result != NULL) *result = res;
  return error;
}
