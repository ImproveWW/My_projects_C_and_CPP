#include "./../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int result_value = 0;                    // Код возврата
  memset(result, 0, sizeof(s21_decimal));  // Обнуляем результат

  int sign_1 = getSign(value_1);  // Знак первого числа
  int sign_2 = getSign(value_2);  // Знак второго числа
  int need_sign =
      (!sign_1 && sign_2) || (sign_1 && !sign_2);  // Определяем знак результата

  delete_sign(&value_1);  // Удаляем знак
  delete_sign(&value_2);

  int pow1 = s21_get_power(value_1);  // Степень первого числа
  int pow2 = s21_get_power(value_2);  // Степень второго числа
  s21_set_power(&value_1, 0);  // Устанавливаем степень 0
  s21_set_power(&value_2, 0);

  s21_decimal temp_result = {0};
  int is_over = s21_multiply(value_1, value_2, &temp_result);  // Умножение
  int count = 0;  // Счетчик делений на 10

  // Обрабатываем переполнение
  if (is_over && (pow1 + pow2) > 0) {
    s21_decimal ten = {{10}};
    while (is_over && count < (pow1 + pow2)) {
      s21_decimal div_res = {{1}};
      s21_decimal delim = count % 2 ? value_2 : value_1;
      s21_int_div(delim, ten, &div_res);
      if (count % 2)
        value_2 = div_res;
      else
        value_1 = div_res;
      is_over = s21_multiply(value_1, value_2, &temp_result);
      count++;
    }
  }

  // Устанавливаем результат
  if (is_over) {
    result_value = need_sign ? 2 : 1;  // Переполнение
  } else {
    *result = temp_result;
    s21_set_power(result, pow1 + pow2 - count);  // Устанавливаем степень
    if (need_sign) set_sign(result);  // Устанавливаем знак
  }

  return result_value;  // Код результата
}

int s21_multiply(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal* result) {
  int is_over = 0;
  int sum_over = 0;
  s21_decimal temp = {0};
  s21_decimal result_tmp = {0};
  int count = 0;

  while (!is_zero(value_2)) {
    memset(&temp, 0, sizeof(s21_decimal));
    int bit_2 = getBit(value_2, 0);

    for (int i = 0; i < 96; i++) {
      if (getBit(value_1, i) && bit_2)
        set_bit(&temp,
                i);  // Если оба бита установлены, устанавливаем бит в temp
    }

    is_over = count_shift(&temp, count);                // Сдвиг влево
    sum_over = s21_sum(result_tmp, temp, &result_tmp);  // Суммируем
    rshift(&value_2);  // Сдвиг вправо

    if (is_over || sum_over) break;  // Переполнение или ошибка
    count++;
  }

  if (!is_over && !sum_over) *result = result_tmp;  // Записываем результат
  return is_over || sum_over;  // Результат: 1 - ошибка, 0 - всё в порядке
}

int count_shift(s21_decimal* value, int count) {
  int is_over = 0;
  for (int i = 0; i < count; i++) {
    is_over = lshift(value);  // Сдвиг влево
    if (is_over) break;
  }
  return is_over;  // Результат сдвига
}

int lshift(s21_decimal* value) {
  int is_over = getBit(*value, 95);  // Переполнение в старшем бите

  // Сдвиг влево
  value->bits[2] <<= 1U;
  if (getBit(*value, 63))
    set_bit(value, 64);  // Устанавливаем бит 64, если бит 63 установлен
  value->bits[1] <<= 1U;
  if (getBit(*value, 31)) set_bit(value, 32);
  value->bits[0] <<= 1U;

  return is_over;  // Переполнение: 1 - да, 0 - нет
}

s21_decimal s21_int_div(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal* result) {
  s21_decimal result_sub = {0};        // Временный результат
  s21_decimal one = {{1}};             // Константа единицы
  s21_decimal temp_value_2 = value_2;  // Копия второго значения
  s21_decimal final_result = {
      0};  // Переменная для хранения финального результата

  // Проверка на случай, если первое значение меньше второго
  if (s21_is_less(value_1, value_2)) {
    final_result = result_sub;  // Результат будет равен 0
  } else if (s21_is_equal(value_1, value_2)) {
    final_result = one;  // Если значения равны, результат равен 1
  } else {
    // Сдвигаем второе значение влево, пока старший бит первого значения больше
    while (find_first_one_bit(value_1) > find_first_one_bit(temp_value_2)) {
      lshift(&temp_value_2);  // Сдвиг второго значения
      lshift(result);         // Сдвиг результата
    }

    // Проверка на случай, если первое значение меньше второго
    if (s21_is_less(value_1, temp_value_2)) {
      rshift(&temp_value_2);  // Сдвиг вправо
      rshift(result);         // Сдвиг результата
    }

    // Вычисляем разность и рекурсивно делим
    s21_sub(value_1, temp_value_2, &result_sub);
    one = s21_int_div(result_sub, value_2, &one);
    s21_sum(*result, one, result);  // Суммируем с текущим результатом
    final_result = *result;  // Сохраняем финальный результат
  }

  *result = final_result;  // Присваиваем финальный результат указателю
  return final_result;  // Возвращаем результат через один return
}

int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int result_value = 0;  // Код возврата для переполнения
  int temp = 0;          // Перенос
  s21_decimal temp_res = {0};  // Временный результат

  for (int i = 0; i < 96; i++) {
    int value1_bit = getBit(value_1, i);
    int value2_bit = getBit(value_2, i);
    int compare = value1_bit || value2_bit;  // Проверка наличия единицы

    if (value1_bit && value2_bit) {
      if (temp) set_bit(&temp_res, i);  // Устанавливаем бит, если есть перенос
      temp = 1;  // Устанавливаем флаг переноса
    } else if (!temp && compare) {
      set_bit(&temp_res, i);  // Устанавливаем бит результата
    } else if (temp && !compare) {
      set_bit(&temp_res,
              i);  // Устанавливаем бит результата и сбрасываем перенос
      temp = 0;
    }

    if (i == 95 && temp == 1) result_value = 1;  // Переполнение в старшем бите
  }

  s21_set_power(&temp_res, s21_get_power(*result));  // Установка степени
  *result = temp_res;  // Записываем результат

  return result_value;  // Возвращаем код результата
}

void rshift(s21_decimal* value) {
  value->bits[0] >>= 1U;  // Сдвигаем младший 32-битный элемент вправо
  if (getBit(*value, 32)) {  // Проверяем, был ли установлен бит 32
    set_bit(value, 31);  // Устанавливаем бит 31 в результате
  }
  value->bits[1] >>= 1U;  // Сдвигаем средний 32-битный элемент вправо
  if (getBit(*value, 64)) {  // Проверяем, был ли установлен бит 64
    set_bit(value, 63);  // Устанавливаем бит 63 в результате
  }
  value->bits[2] >>= 1U;  // Сдвигаем старший 32-битный элемент вправо
}
