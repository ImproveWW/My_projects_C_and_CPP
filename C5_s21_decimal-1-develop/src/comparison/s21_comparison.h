#ifndef SRC_S21_COMPARISON_H_
#define SRC_S21_COMPARISON_H_
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

//

void alignmentScale(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal *increaseScale(s21_decimal *value, int shift);
int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal *leftShift(s21_decimal *value, int shift);
int getBitLast(s21_decimal value);


#endif 