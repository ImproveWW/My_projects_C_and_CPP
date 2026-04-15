#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;

  int scale = s21_get_power(src);
  if (scale) {
    s21_truncate(src, &src);
  }
  int pos = find_first_one_bit(src);
  if (pos > 30) {
    result = 1;
  }
  if (dst == NULL) {
    result = 1;
  } else {
    *dst = 0;
    for (int i = 0; i < 31; i++) {
      int temp = getBit(src, i);
      int power = (1U << i) * temp;
      *dst += power;
    }
    int sign = getSign(src);

    if (sign) {
      *dst *= -1;
    }
  }
  return result;
}
