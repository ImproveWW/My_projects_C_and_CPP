#include "../s21_decimal.h"

#define MAX 79228162514264337593543950335.0F
#define MIN -79228162514264337593543950335.0F
#define S21_POSITIVE_INF 1.0 / 0.0
#define S21_NEGATIVE_INF -1.0 / 0.0

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;  // Переменная для кода результата

  // Проверка на ошибки
  if (src == S21_POSITIVE_INF || src == S21_NEGATIVE_INF || isnan(src) ||
      dst == NULL || (src <= MIN || src >= MAX)) {
    result = 1;  // Устанавливаем код ошибки
  } else {
    memset(dst, 0, sizeof(s21_decimal));  // Обнуляем dst
    int is_negative = src < 0;            // Определяем знак
    long double src_work = fabsl(src);
    long double exp_src = src_work;
    int exp = 0;

    // Получаем количество знаков до десятичной точки
    while (exp_src >= 1) {
      exp_src /= 10.0;
      exp++;
    }
    if (exp == 0) exp = 1;

    src_work *= powl(10.0, 28.0 - exp);  // Домножаем до 28 знаков
    char bit[128] = {'\0'};

    // Преобразуем в двоичный вид
    for (int i = 0; src_work > 1e-6; i++) {
      src_work = floorl(src_work) / 2;
      bit[i] = (src_work - floorl(src_work) > 1e-6) ? '1' : '0';
    }

    // Записываем биты в dst
    for (size_t i = strlen(bit); i > 0; i--) {
      if (bit[i - 1] == '1') {
        set_bit(dst, i - 1);
      }
    }
    s21_set_power(dst, 28 - exp);  // Устанавливаем степень
    if (is_negative) {
      set_sign(dst);  // Устанавливаем знак
    }
  }

  return result;  // Возвращаем код результата
}
