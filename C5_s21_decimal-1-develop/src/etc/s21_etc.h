#ifndef SRC_S21_ETC_H_
#define SRC_S21_ETC_H_
#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
s21_decimal* s21_copy(s21_decimal* dest, s21_decimal src);
s21_decimal *decreaseScale(s21_decimal *value, int shift);
s21_decimal* s21_reset(s21_decimal* value);
int s21_get_exp(s21_decimal value);


#endif 
