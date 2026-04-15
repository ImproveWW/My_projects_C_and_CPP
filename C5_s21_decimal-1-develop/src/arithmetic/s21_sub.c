#include "./../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_value_1 = getSign(value_1);
  int sign_value_2 = getSign(value_2);
  s21_decimal res = {0};
  if (getScale(value_1) != getScale(value_2))
    copmare_positive(&value_1, &value_2);
  int scale = getScale(value_2);
  int error = 0;
  if (sign_value_1 && !sign_value_2) {
    s21_negate(value_2, &value_2);
    error = s21_add(value_1, value_2, &res);
  } else if (!sign_value_1 && sign_value_2) {
    s21_negate(value_2, &value_2);
    error = s21_add(value_1, value_2, &res);
  } else if (sign_value_1 && sign_value_2) {
    s21_negate(value_1, &value_1);
    s21_negate(value_2, &value_2);
    if (s21_is_greater(value_1, value_2)) {
      sub_temp(&value_1, &value_2, &res);
      setSign(&res, 1);
    } else {
      sub_temp(&value_2, &value_1, &res);
      setSign(&res, 0);
    }
  } else {
    if (s21_is_greater(value_2, value_1)) {
      sub_temp(&value_2, &value_1, &res);
      set_sign_2(&res, 1);
    } else {
      sub_temp(&value_1, &value_2, &res);
      set_sign_2(&res, 0);
    }
  }
  set_scale(&res, scale);
  if (result != NULL) *result = res;
  return error;
}