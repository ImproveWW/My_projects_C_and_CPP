#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;  // Изначально считаем числа равными

  if (getSign(value_1) == getSign(value_2)) {
    alignmentScale(&value_1, &value_2);

    for (int i = 95; i >= 0; i--) {
      if (getBit(value_1, i) != getBit(value_2, i)) {
        res = 0;  // Обнаружено несовпадение
        break;
      }
    }
  }

  if (!(getSign(value_1) == getSign(value_2)) &&
      !(isNull(value_1) && isNull(value_2))) {
    res = 0;  // Если знаки различаются и оба значения не нулевые
  }

  return res;  // Возвращаем результат
}
