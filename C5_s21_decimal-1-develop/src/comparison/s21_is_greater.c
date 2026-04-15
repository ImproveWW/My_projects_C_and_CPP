#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int sign_a = getSign(value_1);
  int sign_b = getSign(value_2);

  if (!isNull(value_1) || !isNull(value_2)) {
    if (sign_a != sign_b) {
      res =
          (sign_a == 0) ? 1 : 0;  // Если знаки разные, устанавливаем результат
    } else {
      alignmentScale(&value_1, &value_2);

      for (int i = 95; i >= 0; i--) {
        int bit_a = getBit(value_1, i);
        int bit_b = getBit(value_2, i);

        if (bit_a != bit_b) {
          res = (bit_a != 0) ? (sign_a == 0) : (sign_a == 1);
          break;  // Выход из цикла при обнаружении различий
        }
      }
    }
  }

  return res;  // Возвращаем результат
}

void alignmentScale(s21_decimal *value_1, s21_decimal *value_2) {
  int scale1 = getScale(*value_1);
  int scale2 = getScale(*value_2);

  if (scale1 != scale2) {
    if (scale1 < scale2) {
      // Если scale1 меньше scale2, меняем местами значения
      alignmentScale(value_2, value_1);
    } else {
      int scaleLow = scale2;
      int scaleHigh = scale1;

      // Выравниваем scale2
      while ((scaleHigh - scaleLow) && !getBit(*value_2, 96)) {
        increaseScale(value_2, 1);
        scaleLow += 1;  // Увеличиваем scaleLow
      }

      // Уменьшаем scale1 до scale2
      while (scaleHigh > scaleLow) {
        decreaseScale(value_1, scaleHigh - scaleLow);
        setScale(value_1, scaleLow);
        scaleHigh -= 1;  // Уменьшаем scaleHigh
      }
    }
  }
}

s21_decimal *increaseScale(s21_decimal *value, int shift) {
  int newScale = getScale(*value) + shift;

  if (newScale < 29) {
    setScale(value, newScale);

    s21_decimal auxValue_1 = *value;
    s21_decimal auxValue_2 = *value;

    // Проверяем результат операции добавления битов
    if (addBit(*leftShift(&auxValue_1, 1), *leftShift(&auxValue_2, 3), value)) {
      setBit(value, 96, 1);
    }
  }

  return value;
}

int addBit(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int fres = 0, exp = 0;

  for (int i = 0; i < 96; i++) {
    int bitValue_1 = getBit(value_1, i);
    int bitValue_2 = getBit(value_2, i);

    // Логика вычисления бита результата
    if (!bitValue_1 && !bitValue_2) {
      setBit(result, i, exp ? (exp = 0) + 1 : 0);
    } else if (bitValue_1 != bitValue_2) {
      setBit(result, i, exp ? (exp = 1) - 1 : 1);
    } else {
      setBit(result, i, exp ? (exp = 1) : (exp = 1) - 1);
    }

    // Проверка на переполнение
    if (i == 95 && exp == 1 && !getBit(value_1, 97) && !getBit(value_2, 97)) {
      fres = 1;
    }
  }

  return fres;
}

s21_decimal *leftShift(s21_decimal *value, int shift) {
  if (!(getBitLast(*value) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bitTransfer_1 = getBit(*value, 31);
      int bitTransfer_2 = getBit(*value, 63);
      for (int x = 0; x < 3; x += 1) value->bits[x] <<= 1;
      if (bitTransfer_1) setBit(value, 32, 1);
      if (bitTransfer_2) setBit(value, 64, 1);
    }
  }
  return value;
}

int getBitLast(s21_decimal value) {
  int bitLast = 95;
  while (bitLast >= 0 && !getBit(value, bitLast)) {
    bitLast -= 1;
  }
  return bitLast;
}