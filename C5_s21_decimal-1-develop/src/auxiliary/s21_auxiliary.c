#include "./../s21_decimal.h"

int getSign(s21_decimal value) {
  // Извлечение знака через побитовый сдвиг и маску
  int signBit = 31;  // Позиция знакового бита
  unsigned int signMask = 1u << signBit;
  return (value.bits[3] & signMask) != 0;
}

int getScale(s21_decimal value) {
  int scaleStartBit = 16;
  int scaleBitMask = 0xFF << scaleStartBit;
  return (value.bits[3] & scaleBitMask) >> scaleStartBit;
}

int getBit(s21_decimal value, int position) {
  int posInArray = position / 32;  // Определение индекса массива
  int posInBit = position % 32;  // Определение позиции в элементе
  unsigned int bitMask = 1u << posInBit;  // Маска для бита
  return (value.bits[posInArray] & bitMask) != 0;
}

int isNull(s21_decimal value) {
  return (value.bits[0] | value.bits[1] | value.bits[2]) == 0;
}

s21_decimal *setScale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {  // Проверяем допустимость масштаба
    int mask = 0xFF << 16;  // Маска для обнуления битов масштаба
    value->bits[3] &= ~mask;  // Сбрасываем текущий масштаб
    int scaleBits = scale << 16;  // Подготавливаем новые биты масштаба
    value->bits[3] |= scaleBits;  // Устанавливаем новый масштаб
    if (getSign(*value)) setSign(value, 1);  // Восстанавливаем знак
  }
  return value;  // Возвращаем модифицированное значение
}

s21_decimal *setSign(s21_decimal *value, int sign) {
  int signBit = 1 << 31;  // Маска для знакового бита
  if (sign) {
    value->bits[3] |= signBit;  // Устанавливаем бит знака
  } else {
    value->bits[3] &= ~signBit;  // Сбрасываем бит знака
  }
  return value;  // Возвращаем результат
}

s21_decimal *setBit(s21_decimal *value, int pos, int bit) {
  if (pos < 128) {  // Проверка допустимости позиции бита
    int index = pos / 32;  // Определяем индекс элемента массива
    int offset = pos % 32;  // Позиция внутри элемента массива
    int bitMask = 1 << offset;  // Маска для нужного бита
    if (bit) {
      value->bits[index] |= bitMask;  // Устанавливаем бит
    } else {
      value->bits[index] &= ~bitMask;  // Сбрасываем бит
    }
  }
  return value;  // Возвращаем измененное значение
}

// Arithmetic

void setSignInt(int sign, s21_decimal *dst) {
  if (sign == 1) {
    dst->bits[3] |= MINUS;
  } else if (sign == 0) {
    dst->bits[3] &= PLUS;
  }
}

s21_decimal convert_ll_to_decimal(long long val) {
  s21_decimal res = {0};
  if (val < 0) {
    setSignInt(1, &res);
    val = -val;
  }

  for (uint64_t i = 0; val; i++, val /= 2) {
    if (val % 2) {
      res.bits[i / 32] |= (1U << i);
    }
  }
  return res;
}

long long random_ll() {
  long long val = 0;
  for (uint64_t i = 0; i < 64; i++) {
    if (rand() % 2) {
      val |= (1U << i);
    }
  }
  return val;
}

float random_float(float min, float max) {
  float result = 0;
  float random = (float)rand() / (float)RAND_MAX;
  float range = max - min;
  result = random * range + min;
  return result;
}

int s21_get_power(s21_decimal value) {
  int power = 0;
  int result = 0;
  for (int i = 0; i < 23 - 16; i++) {
    int temp = getBit(value, 96 + i + 16);
    power = (1U << i) * temp;
    result += power;
  }
  return result;
}

int find_first_one_bit(s21_decimal src) {
  int position = -1;
  for (int i = 95; i >= 0; i--) {
    if (getBit(src, i)) {
      position = i;
      break;
    }
  }
  return position;
}

void set_bit(s21_decimal *number, int position) {
  int mask = 1U << (position % 32);
  number->bits[position / 32] |= mask;
}

void set_sign(s21_decimal *number) {
  int mask = 1U << 31;
  number->bits[3] |= mask;
}

void set_sign_2(s21_decimal *num, int sign) { num->bits[3] |= sign << 31; }

void s21_delete_power(s21_decimal *value) {
  int sign = getSign(*value);
  value->bits[3] = 0;
  if (sign) {
    set_sign(value);
  }
}

void s21_set_power(s21_decimal *value, int pow) {
  s21_delete_power(value);
  for (int i = 16; i <= 23 && pow; i++) {
    if (pow % 2 == 1) {
      set_bit(value, 96 + i);
    }
    pow /= 2;
  }
}

int is_zero(s21_decimal number) {
  int result =
      number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0;
  return result;
}

void delete_sign(s21_decimal *number) {
  int mask = ~(1U << 31);
  number->bits[3] &= mask;
}

int mul10(s21_decimal *value) {
  int overflow = 0;
  s21_decimal temp_value = *value;
  unsigned long long int temp = 0;
  for (int i = 0; i < 3; i++) {
    temp = (unsigned long long int)value->bits[i] * 10 + overflow;
    overflow = temp / (1LLU << 32);
    value->bits[i] = temp % (1LLU << 32);
  }
  if (overflow) *value = temp_value;
  return overflow;
}

void set_scale(s21_decimal *num, int scale) { num->bits[3] |= scale << 16; }

int mul10_pre(s21_decimal value) {
  int overflow = 0;
  unsigned long long int temp = 0;
  for (int i = 0; i < 3; i++) {
    temp = (unsigned long long int)value.bits[i] * 10 + overflow;
    overflow = temp / (1LLU << 32);
    value.bits[i] = temp % (1LLU << 32);
  }
  return overflow;
}

void del10(s21_decimal *value) {
  unsigned int temp = 0;
  uint64_t ost = 0;
  for (int i = 2; i >= 0; i--) {
    ost = value->bits[i] + ((int64_t)temp << 32);
    temp = ost % 10;
    value->bits[i] = ost / 10;
  }
}

uint64_t mod10(s21_decimal value) {
  unsigned int temp = 0;
  uint64_t ost = 0;
  for (int i = 2; i >= 0; i--) {
    ost = value.bits[i] + ((int64_t)temp << 32);
    temp = ost % 10;
  }
  return temp;
}

void set_bit_2(s21_decimal *number, int bit, int sign) {
  if (sign == 0) {
    number->bits[bit / 32] = number->bits[bit / 32] & ~(1 << bit % 32);
  } else {
    number->bits[bit / 32] = number->bits[bit / 32] | (1 << bit % 32);
  }
}

void bank(s21_decimal *value) {
  s21_decimal res;
  s21_decimal five = {{5}};
  s21_decimal one = {{1}};
  int scale_value = getScale(*value);
  int compare = mod10(*value);
  if (compare == 5) {
    del10(value);
    add_temp(*value, one, &res);
    set_bit_2(&res, 0, 0);
  } else {
    add_temp(*value, five, &res);
    del10(&res);
  }
  (scale_value)--;
  setScale(&res, scale_value);
  *value = res;
}

void initial_num(s21_decimal *number) {
  for (int i = 0; i < 128; i++) {
    set_bit_2(number, i, 0);
  }
}

void scale_comper_help(int *scale_value_2, int *scale_value_1,
                       s21_decimal *value_2, s21_decimal *value_1) {
  s21_decimal res;
  s21_decimal five = {{5}};
  s21_decimal one = {{1}};
  while (*scale_value_2 - *scale_value_1 != 0 && mul10_pre(*value_1) == 0) {
    mul10(value_1);
    (*scale_value_1)++;
  }
  if (*scale_value_1 != *scale_value_2) {
    while (*scale_value_2 - *scale_value_1 != 1) {
      // if (mod10(*value_2) != 0) flag = 1;
      del10(value_2);
      (*scale_value_2)--;
    }
    int compare = mod10(*value_2);
    if (compare == 5) {
      del10(value_2);
      add_temp(*value_2, one, &res);
      set_bit_2(&res, 0, 0);
    } else {
      add_temp(*value_2, five, &res);
      del10(&res);
      setScale(&res, *scale_value_2);
    }
    *value_2 = res;
    (*scale_value_2)--;
  }
  // printf("%d %d\n", *scale_value_2, *scale_value_1);
}

void scale_compare(s21_decimal *value_1, s21_decimal *value_2) {
  int scale_value_1 = getScale(*value_1);
  int scale_value_2 = getScale(*value_2);
  if (scale_value_1 > scale_value_2) {
    scale_comper_help(&scale_value_1, &scale_value_2, value_1, value_2);
  } else if (scale_value_1 < scale_value_2) {
    scale_comper_help(&scale_value_2, &scale_value_1, value_2, value_1);
  }
  setScale(value_1, scale_value_1);
  setScale(value_2, scale_value_2);
}

void copmare_positive(s21_decimal *value_1, s21_decimal *value_2) {
  int sign_value_1 = getSign(*value_1);
  int sign_value_2 = getSign(*value_2);
  if (sign_value_1 && sign_value_2) {
    s21_negate(*value_1, value_1);
    s21_negate(*value_2, value_2);
    scale_compare(value_1, value_2);
    s21_negate(*value_1, value_1);
    s21_negate(*value_2, value_2);
  } else if (sign_value_1) {
    s21_negate(*value_1, value_1);
    scale_compare(value_1, value_2);
    s21_negate(*value_1, value_1);
  } else if (sign_value_2) {
    s21_negate(*value_2, value_2);
    scale_compare(value_1, value_2);
    s21_negate(*value_2, value_2);
  } else
    scale_compare(value_1, value_2);
}

int add_temp(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  initial_num(result);
  int overflow = 0;
  long long int temp_result = 0;
  for (int i = 0; i < 3; i++) {
    temp_result = (long long int)value_1.bits[i] + value_2.bits[i] + overflow;
    if (temp_result > __UINT32_MAX__)
      overflow = 1;
    else
      overflow = 0;
    result->bits[i] = temp_result;
  }
  return overflow;
}

void s21_nullify(s21_decimal *num) {
  num->bits[0] = 0;
  num->bits[1] = 0;
  num->bits[2] = 0;
  num->bits[3] = 0;
}

void sub_temp(s21_decimal *val_1, s21_decimal *val_2, s21_decimal *result) {
  initial_num(result);
  unsigned overflow = 1;
  for (int i = 0; i < 3; i++) {
    unsigned long long tmp =
        (unsigned long long)val_1->bits[i] + ~val_2->bits[i] + overflow;
    overflow = tmp / (1LLU << 32);
    result->bits[i] = tmp % (1LLU << 32);
  }
}

//

s21_decimal s21_bank_rounding(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal last_decimal = {0};
  s21_decimal result = {{1}};

  s21_mod(value, ten, &last_decimal);
  s21_decimal pre_digit = s21_get_pre_digit(value);
  s21_int_div(value, ten, &result);

  return s21_base_bank_round(last_decimal, pre_digit, result);
}

int s21_normalization(s21_decimal *value_1, s21_decimal *value_2) {
  int check_over = 0;
  int power_1 = s21_get_power(*value_1);
  int power_2 = s21_get_power(*value_2);
  s21_set_power(value_1, 0);
  s21_set_power(value_2, 0);

  int biggest_power = power_1 > power_2 ? power_1 : power_2;
  int min_power = power_1 < power_2 ? power_1 : power_2;
  s21_decimal num_normalize = power_1 < power_2 ? *value_1 : *value_2;
  s21_decimal small = power_1 < power_2 ? *value_2 : *value_1;
  s21_decimal result = {0};
  s21_decimal ten = {{10}};

  while (min_power != biggest_power) {
    check_over = s21_multiply(num_normalize, ten, &result);
    if (check_over) {
      break;
    }
    min_power++;
    num_normalize = result;
    memset(&result, 0, sizeof(s21_decimal));
  }
  if (check_over) {
    while (min_power < biggest_power) {
      small = s21_bank_rounding(small);
      min_power++;
    }
  }
  if (power_1 < power_2) {
    *value_1 = num_normalize;
    *value_2 = small;
  } else {
    *value_2 = num_normalize;
    *value_1 = small;
  }
  s21_set_power(value_1, biggest_power);
  s21_set_power(value_2, biggest_power);
  return check_over;
}

s21_decimal s21_get_pre_digit(s21_decimal value) {
  s21_decimal ten = {{10}};
  s21_decimal div_result = {{1}};
  s21_decimal pre_digit = {0};
  s21_int_div(value, ten, &div_result);
  s21_mod(div_result, ten, &pre_digit);
  return pre_digit;
}

s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result) {
  s21_decimal two = {{2}};
  s21_decimal five = {{5}};
  s21_decimal is_even = {0};

  // Округление по банковским правилам
  if (s21_is_equal(last_decimal, five)) {
    s21_mod(pre_digit, two, &is_even);
    if (!is_zero(is_even)) {
      s21_plus_one(result, &result);
    }
  } else if (s21_is_greater(last_decimal, five)) {
    s21_plus_one(result, &result);
  }

  return result;
}

s21_decimal s21_inversion(s21_decimal number) {
  s21_decimal result;
  result.bits[0] = ~number.bits[0];
  result.bits[1] = ~number.bits[1];
  result.bits[2] = ~number.bits[2];
  return result;
}

void s21_plus_one(s21_decimal value, s21_decimal *result) {
  s21_decimal one = {0};
  one.bits[0] = 1;
  s21_sum(value, one, result);
}

s21_decimal s21_binary_mod(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal result_sub = {0};
  s21_decimal result = {0};
  s21_decimal temp_value_2 = value_2;
  if (s21_is_less(value_1, value_2)) {
    return value_1;
  } else if (s21_is_equal(value_1, value_2)) {
    return result_sub;
  }
  while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
    lshift(&temp_value_2);
  }
  if (s21_is_less(value_1, temp_value_2)) {
    rshift(&temp_value_2);
  }
  s21_sub(value_1, temp_value_2, &result_sub);
  result = s21_binary_mod(result_sub, value_2);
  return result;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  if (is_zero(value_2)) {
    return 3;
  }
  int sign = getSign(value_1);
  delete_sign(&value_1);
  delete_sign(&value_2);
  int pow_1 = s21_get_power(value_1);
  int pow_2 = s21_get_power(value_2);
  int is_over = s21_normalization(&value_1, &value_2);
  if (is_over && is_zero(value_2)) {
    return 0;
  }
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);
  *result = s21_binary_mod(value_1, value_2);
  if (sign) {
    set_sign(result);
  }
  int max = pow_1 > pow_2 ? pow_1 : pow_2;
  s21_set_power(result, max);
  if (is_over) {
    s21_truncate(*result, result);
  }
  return 0;
}
