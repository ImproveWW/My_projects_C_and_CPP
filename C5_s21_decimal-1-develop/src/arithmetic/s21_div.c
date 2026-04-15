#include "../s21_decimal.h"

s21_decimal s21_binary_div(s21_decimal value_1, s21_decimal value_2,
                           s21_decimal *result) {
  static unsigned int pre_digit = 0;
  s21_decimal temp_result = {{1}};
  s21_decimal result_sub = {0};
  s21_decimal one = {{1}};
  s21_decimal ten = {{10}};
  s21_decimal temp_value_2 = value_2;
  s21_decimal final_result = {0};  // Итоговый результат

  if (s21_is_less(value_1, value_2)) {
    if (!is_zero(value_1)) {
      int is_over = 0;
      int power = s21_get_power(*result);
      if (power == 28) {
        is_over = 1;
      } else {
        is_over = s21_multiply(*result, ten, result);
      }
      power += 1;
      s21_multiply(value_1, ten, &value_1);
      if (is_over) {
        s21_int_div(value_1, value_2, &temp_result);
        s21_decimal pre_digit_dec = {{pre_digit}};
        *result = s21_base_bank_round(temp_result, pre_digit_dec, *result);
        final_result =
            result_sub;  // Выход из функции через финальный результат
      } else {
        s21_set_power(result, power);
        pre_digit = 0;
        final_result = s21_binary_div(value_1, value_2, result);
      }
    } else {
      final_result = result_sub;
    }
  } else if (s21_is_equal(value_1, value_2)) {
    s21_sum(*result, one, result);
    final_result = one;  // Если числа равны
  } else {
    while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
      lshift(&temp_value_2);
      lshift(&temp_result);
    }
    if (s21_is_less(value_1, temp_value_2)) {
      rshift(&temp_value_2);
      rshift(&temp_result);
    }
    s21_sum(*result, temp_result, result);
    s21_sub(value_1, temp_value_2, &result_sub);
    pre_digit += temp_result.bits[0];
    final_result = s21_binary_div(result_sub, value_2, result);
  }

  return final_result;  // Один return для всех случаев
}

s21_decimal s21_normalize_after_div(s21_decimal result_dif, int power_1,
                                    int power_2) {
  int difference;
  s21_decimal ten = {{10}};
  if (power_1 > power_2) {
    difference = power_1 - power_2;
    int result_power = s21_get_power(result_dif) + difference;
    if (result_power > 28) {
      result_power = 28;
    }
    s21_set_power(&result_dif, result_power);
  } else if (power_1 < power_2) {
    difference = power_2 - power_1;
    int result_power = s21_get_power(result_dif) - difference;
    result_power = result_power < 0 ? 0 : result_power;
    s21_set_power(&result_dif, 0);
    while (difference) {
      s21_multiply(result_dif, ten, &result_dif);
      difference--;
    }
    s21_set_power(&result_dif, result_power);
  }
  return result_dif;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_value = 0;  // Переменная для кода возврата
  memset(result, 0, sizeof(s21_decimal));

  int sign_1 = getSign(value_1);
  int sign_2 = getSign(value_2);
  int result_sign = 0;
  s21_decimal one = {{1}};

  delete_sign(&value_1);
  delete_sign(&value_2);
  int pow1 = s21_get_power(value_1);
  int pow2 = s21_get_power(value_2);

  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    result_sign = 1;
  }

  if (is_zero(value_2)) {
    result_value = 3;  // Ошибка деления на 0
  } else if (s21_is_equal(value_2, one)) {
    *result = value_1;
    if (result_sign) set_sign(result);
  } else {
    int is_over = s21_check_over(value_1, value_2);
    if (is_over) {
      if ((!sign_1 && !sign_2) || (sign_1 && sign_2)) {
        result_value = 1;
      } else if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
        result_value = 2;
      }
    } else {
      s21_set_power(&value_1, 0);
      s21_set_power(&value_2, 0);
      if (pow1 > pow2) s21_set_power(result, pow1);
      s21_binary_div(value_1, value_2, result);
      *result = s21_normalize_after_div(*result, pow1, pow2);

      if (result_sign) {
        set_sign(result);
      }
    }
  }

  return result_value;  // Один return для всех случаев
}

int s21_check_over(s21_decimal value_1, s21_decimal value_2) {
  int check_over = 0;
  int power_1 = s21_get_power(value_1);
  int power_2 = s21_get_power(value_2);
  s21_set_power(&value_1, 0);
  s21_set_power(&value_2, 0);

  int biggest_power = power_1 > power_2 ? power_1 : power_2;
  int min_power = power_1 < power_2 ? power_1 : power_2;
  s21_decimal num_normalize = power_1 < power_2 ? value_1 : value_2;
  s21_decimal small = power_1 < power_2 ? value_2 : value_1;
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
    if (is_zero(small)) {
      return check_over;
    }
  }
  return 0;
}
