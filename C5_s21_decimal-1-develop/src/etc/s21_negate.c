#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    s21_nullify(result);
    *result = value;
    setSign(result, (!getSign(*result)));
  } else {
    error = 1;
  }
  return error;
}
