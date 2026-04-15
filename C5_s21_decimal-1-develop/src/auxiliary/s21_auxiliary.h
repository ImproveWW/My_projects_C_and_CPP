#ifndef SRC_S21_AUXILIARY_H_
#define SRC_S21_AUXILIARY_H_
#include "./../s21_decimal.h"
#include <stdint.h>

int getSign(s21_decimal value);

int getScale(s21_decimal value);
int getBit(s21_decimal value, int position);
int isNull(s21_decimal value);
s21_decimal *setScale(s21_decimal *value, int scale);
s21_decimal *setSign(s21_decimal *value, int sign);
s21_decimal *setBit(s21_decimal *value, int pos, int bit);

//Arithmetic
void setSignInt(int sign, s21_decimal *dst);
s21_decimal convert_ll_to_decimal(long long val);
long long random_ll();
float random_float(float min, float max);
int s21_get_power(s21_decimal value) ;
int find_first_one_bit(s21_decimal src);
void set_bit(s21_decimal* number, int position);
void set_sign(s21_decimal* number);
void s21_delete_power(s21_decimal* value);
void s21_set_power(s21_decimal* value, int pow);
int is_zero(s21_decimal number);
void delete_sign(s21_decimal* number);
int mul10(s21_decimal *value);
void set_scale(s21_decimal *num, int scale);
int mul10_pre(s21_decimal value);
void del10(s21_decimal *value);
uint64_t mod10(s21_decimal value);
void set_bit_2(s21_decimal* number, int bit, int sign);
void initial_num(s21_decimal* number);
void scale_comper_help(int *scale_value_2, int *scale_value_1, s21_decimal *value_2, s21_decimal *value_1);
void scale_compare(s21_decimal *value_1, s21_decimal *value_2);
void copmare_positive(s21_decimal *value_1, s21_decimal *value_2);
int add_temp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void bank(s21_decimal *value);
void s21_nullify(s21_decimal *num);
void set_sign_2(s21_decimal *num, int sign);
void sub_temp(s21_decimal *val_1, s21_decimal *val_2, s21_decimal *result);

//
int s21_normalization(s21_decimal* value_1, s21_decimal* value_2);
s21_decimal s21_bank_rounding(s21_decimal value);
s21_decimal s21_get_pre_digit(s21_decimal value);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal s21_binary_mod(s21_decimal value_1, s21_decimal value_2);
s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result);
s21_decimal s21_inversion(s21_decimal number);
void s21_plus_one(s21_decimal value, s21_decimal* result);
//




#endif