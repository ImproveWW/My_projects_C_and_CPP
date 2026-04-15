#ifndef SRC_S21_ARITHMETIC_H_
#define SRC_S21_AUXILIARY_H_

#include "../s21_decimal.h"

int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *result);

//
int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal* result);
int count_shift(s21_decimal* value, int count);
int lshift(s21_decimal* value);
s21_decimal s21_int_div(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal* result);
int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
void rshift(s21_decimal* value);
//
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//
int s21_check_over(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_normalize_after_div(s21_decimal result_dif, int power_1,
                                    int power_2);
s21_decimal s21_binary_div(s21_decimal value_1, s21_decimal value_2,
                                  s21_decimal *result);
//
int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);



#endif