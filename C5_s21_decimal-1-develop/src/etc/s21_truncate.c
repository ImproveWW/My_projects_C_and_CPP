#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal* result) {
  s21_copy(s21_reset(result),
           getScale(value) ? *decreaseScale(&value, getScale(value)) : value);
  return 0;
}

s21_decimal* s21_copy(s21_decimal* dest, s21_decimal src) {
  for (int x = 0; x < 4; x += 1) dest->bits[x] = src.bits[x];
  return dest;
}

s21_decimal* decreaseScale(s21_decimal* value, int shift) {
  // Уменьшаем масштаб числа на заданное количество единиц.
  for (int y = 0; y < shift; y++) {
    unsigned long long overflow = value->bits[2];  // Сохраняем старший бит
    for (int x = 2; x >= 0; x--) {
      value->bits[x] = overflow / 10;  // Вычисляем новое значение для бита
      overflow = (overflow % 10) * (4294967295 + 1) +
                 value->bits[x ? x - 1 : x];  // Обновляем overflow
    }
  }
  setScale(value, (getScale(*value) - shift));  // Устанавливаем новый масштаб
  return value;  // Возвращаем модифицированное значение
}

s21_decimal* s21_reset(s21_decimal* value) {
  for (int x = 0; x < 4; x += 1) value->bits[x] = 0;
  return value;
}