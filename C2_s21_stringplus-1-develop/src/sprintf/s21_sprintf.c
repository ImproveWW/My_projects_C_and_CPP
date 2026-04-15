#include "../s21_string.h"

// MARK: S21_PRINTF
int s21_sprintf(char *buffer, const char *format, ...) {
  if (buffer == s21_NULL || format == s21_NULL) return -1;

  size_t buffer_size = s21_strlen(buffer);
  s21_memset(buffer, '\0', buffer_size);  // обнуление буфера

  Options options = {false, false, false, false, false, false, false,
                     false, 1,     6,     false, false, false};
  char *buffer_ptr = buffer;

  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    if (*format == '%') {
      format++;
      format = parse_options(&options, format, args);

      if (!is_specifier(*format)) {
        s21_memset(buffer, '\0', buffer_size);
        return -1;
      }

      switch_specifier(buffer, format, args, options);
      if (options.has_error) {
        s21_memset(buffer, '\0', buffer_size);
        return -1;
      }
      set_default(&options);
    } else {
      while (*buffer_ptr != '\0') buffer_ptr++;
      *buffer_ptr = *format;
    }
    format++;
  }
  va_end(args);
  return s21_strlen(buffer);

  // освобождение памяти
  s21_memset(buffer, '\0', buffer_size);
  free(buffer);
  return s21_strlen(buffer);
}

// MARK: SPECIFIER FUNC
char *switch_specifier(char *buffer, const char *format, va_list args,
                       Options options) {
  switch (*format) {
    case '%':
      s21_strncat(buffer, "%%", 1);
      break;
    case 'c':
      process_c_specifier(buffer, args, options);  // "с" для символа
      break;
    case 'd':
      process_d_specifier(buffer, args, options);  // "d" для целых чисел
      break;
    case 'f':
      process_f_specifier(buffer, args,
                          options);  // 'f' для чисел с плавающей точкой
      break;
    case 's':
      process_s_specifier(buffer, args, options);  // 's' для строк
      break;
    case 'u':
      process_u_specifier(buffer, args,
                          options);  // 'u' для беззнаковых целых чисел
      break;
    case 'e':
      process_e_specifier(buffer, args,
                          options);  // 'e' для чисел в экспоненциальной форме
      break;
    case 'E':
      options.has_big_E_character = true;
      process_e_specifier(buffer, args, options);
      break;
    case 'g':
      process_g_specifier(
          buffer, args,
          options);  // 'g' для вывода числа в наиболее компактной форме
      break;
    case 'G':
      options.has_big_E_character = true;
      process_g_specifier(buffer, args, options);
      break;
    case 'x':
      process_x_specifier(
          buffer, args,
          options);  // 'x' для вывода числа в шестнадцатеричной системе
      break;
    case 'X':
      options.upper_case = true;
      process_x_specifier(buffer, args, options);
      break;
    case 'p':
      process_p_specifier(buffer, args, options);  // 'p' для вывода указателя
      break;
    case 'o':
      process_o_specifier(
          buffer, args,
          options);  // 'o' для вывода числа в восьмеричной системе
      break;
    default:
      break;
  }
  return buffer;
}

// символ
void process_c_specifier(char *buffer, va_list args, Options options) {
  char str[2];
  int c = va_arg(args, int);
  str[0] = c;
  str[1] = '\0';

  char *empty_str = make_empty_str(options, 1);

  // иф выравнивание по правому краю, сначала добавляем пустую строку
  if ((!options.left_justification) && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, str, 1);

  // иф выравнивание по левому краю, добавляем пустую строку после символа
  if ((options.left_justification) && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (empty_str != s21_NULL) free(empty_str);
}

// Знаковое десятичное целое число
void process_d_specifier(char *buffer, va_list args, Options options) {
  long long value = get_int_value(options, args);

  char *prefix = add_prefix((value < 0), options);

  char *str = int_to_str(llabs(value));

  char *empty_str =
      make_empty_str(options, (s21_strlen(prefix) + s21_strlen(str)));

  if (!options.left_justification && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, prefix, s21_strlen(prefix));
  s21_strncat(buffer, str, s21_strlen(str));

  if (options.left_justification && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (str != s21_NULL) free(str);
  if (prefix != s21_NULL) free(prefix);
  if (empty_str != s21_NULL) free(empty_str);
}
// Десятичное число с плавающей точкой
void process_f_specifier(char *buffer, va_list args, Options options) {
  long double value = get_float_value(options, args);
  char *str = double_to_str(fabsl(value), options);
  char *empty_str = make_empty_str(options, s21_strlen(str));
  if (!options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));
  s21_strncat(buffer, str, s21_strlen(str));
  if (options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (str != s21_NULL) free(str);
  if (empty_str != s21_NULL) free(empty_str);
}

// строка символов
void process_s_specifier(char *buffer, va_list args, Options options) {
  char *str = va_arg(args, char *);
  char *empty_str = make_empty_str(options, s21_strlen(str));

  if ((!options.left_justification) && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, str, s21_strlen(str));

  if ((options.left_justification) && (empty_str != s21_NULL))
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (empty_str != s21_NULL) free(empty_str);
}

// Беззнаковое десятичное целое число
void process_u_specifier(char *buffer, va_list args, Options options) {
  unsigned long long value = get_unsigned_int_value(options, args);

  char *prefix = add_prefix(false, options);
  char *str = int_to_str(value);
  char *empty_str =
      make_empty_str(options, (s21_strlen(prefix) + s21_strlen(str)));

  if (!options.left_justification && str != s21_NULL)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, str, s21_strlen(str));

  if (options.left_justification && str != s21_NULL)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (str != s21_NULL) free(str);
  if (prefix != s21_NULL) free(prefix);
  if (empty_str != s21_NULL) free(empty_str);
}

// Научная нотация (мантисса/экспонента) с использованием символа e
//(вывод чисел должен совпадать с точностью до e-6)
void process_e_specifier(char *buffer, va_list args, Options options) {
  long double value = get_float_value(options, args);
  char *result_str = double_to_enotation(value, options);
  char *empty_str = make_empty_str(options, s21_strlen(result_str));

  if (!options.left_justification && empty_str != s21_NULL)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, result_str, s21_strlen(result_str));

  if (options.left_justification && empty_str != s21_NULL)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (result_str != s21_NULL) free(result_str);
  if (empty_str != s21_NULL) free(empty_str);
}

// Использует кратчайший из представлений десятичного числа
void process_g_specifier(char *buffer, va_list args, Options options) {
  long double value = get_float_value(options, args);
  char *str1 = double_to_str(value, options);
  char *str2 = double_to_enotation(value, options);

  // выбираем более компактное представление
  char *result = s21_strlen(str1) > s21_strlen(str2) ? str2 : str1;

  s21_strncat(buffer, result, s21_strlen(result));

  if (str1 != s21_NULL) free(str1);
  if (str2 != s21_NULL) free(str2);
}

// Беззнаковое шестнадцатеричное целое число
void process_x_specifier(char *buffer, va_list args, Options options) {
  char *str = uint_to_hex_str(va_arg(args, unsigned int), options.upper_case);
  char *empty_str = make_empty_str(options, s21_strlen(str));

  if (!options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  s21_strncat(buffer, str, s21_strlen(str));

  if (options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (str != s21_NULL) free(str);
  if (empty_str != s21_NULL) free(empty_str);
}

// Адрес указателя
void process_p_specifier(char *buffer, va_list args, Options options) {
  void *ptr = va_arg(args, void *);
  unsigned long long value =
      (unsigned long long)ptr;  // преобразуем указатель в числовое значение

  char result_str[100] = "\0";
  char *hex_str = uint_to_hex_str(value, options.upper_case);

  s21_strncat(result_str, "0", 1);
  s21_strncat(result_str, "x", 1);
  s21_strncat(result_str, hex_str, s21_strlen(hex_str));

  char *empty_str = make_empty_str(options, s21_strlen(result_str));

  if (!options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));
  s21_strncat(buffer, result_str, s21_strlen(result_str));
  if (options.left_justification)
    s21_strncat(buffer, empty_str, s21_strlen(empty_str));

  if (hex_str != s21_NULL) free(hex_str);
  if (empty_str != s21_NULL) free(empty_str);
}

// Беззнаковое восьмеричное число
void process_o_specifier(char *buffer, va_list args, Options options) {
  int value = va_arg(args, int);
  char *int_str;
  char str[100];
  s21_memset(str, '\0', 100);

  while (value != 0) {
    int_str = int_to_str(value % 8);
    s21_strncat(str, int_str, 1);
    value /= 8;
    if (int_str != s21_NULL) free(int_str);
  }
  reverse_string(
      str);  // переворачиваем строку, тк цифры добавлялись в обратном порядке

  char *empty_string = make_empty_str(options, s21_strlen(str));

  if (!options.left_justification)
    s21_strncat(buffer, empty_string, s21_strlen(empty_string));
  s21_strncat(buffer, str, s21_strlen(str));
  if (options.left_justification)
    s21_strncat(buffer, empty_string, s21_strlen(empty_string));

  if (empty_string != s21_NULL) free(empty_string);
}

// MARK: HELPERS

// преобразует целое число в строку
char *int_to_str(long long value) {
  if (value == 0) {
    char *zero_str = malloc(2);
    if (zero_str == NULL) {
      return NULL;
    }
    zero_str[0] = '0';
    zero_str[1] = '\0';
    return zero_str;
  }

  long long temp = value;
  int charecters_number = 0;
  while (temp != 0) {
    charecters_number++;
    temp /= 10;
  }

  char *result = malloc(sizeof(char) * (charecters_number + 2));
  if (result == NULL) {
    return NULL;
  }

  result[charecters_number] = '\0';

  int i = charecters_number - 1;
  while (value != 0) {
    result[i--] = (value % 10) + '0';
    value /= 10;
  }

  return result;
}

// преобразует число с плавающей точкой в строку, учитывая настройки опций
char *double_to_str(long double value, Options options) {
  char *result_str;
  char *prefix = add_prefix(((int)value < 0), options);

  long long whole_part = (long long)value;  // целая часть числа
  long double decimal_part = fabsl(value - whole_part);  // дробная часть числа

  char *whole_part_str = int_to_str(whole_part);

  s21_size_t result_str_len =
      s21_strlen(prefix) + s21_strlen(whole_part_str) +
      ((options.precision_description + 2) * sizeof(char));
  result_str = (char *)malloc(result_str_len);
  if (result_str == s21_NULL) return s21_NULL;
  for (s21_size_t i = 0; i < result_str_len; i++) result_str[i] = '\0';

  s21_strncat(result_str, prefix, s21_strlen(prefix));
  s21_strncat(result_str, whole_part_str, s21_strlen(whole_part_str));
  if (options.precision_description > 0 ||
      (options.precision_description == 0 && options.alternative_form))
    s21_strncat(result_str, ".", 1);

  char decimal_str[100] = "\0";
  char *ptr = decimal_str;

  while (options.precision_description > 0) {
    decimal_part *= 10;
    int digit = (int)decimal_part;
    *ptr = '0' + digit;
    ptr++;
    decimal_part -= digit;
    options.precision_description--;
  }
  *ptr = '\0';

  s21_strncat(result_str, decimal_str, s21_strlen(decimal_str));

  if (prefix != s21_NULL) free(prefix);
  if (whole_part_str != s21_NULL) free(whole_part_str);
  return result_str;
}

// Преобразует число с плавающей точкой в строку в экспоненциальной нотации
char *double_to_enotation(long double value, Options options) {
  char *result_str;
  char *prefix = add_prefix((value < 0), options);

  long double mantissa = fabsl(value);
  int exponent = 0;
  // вычисляем значение мантиссы и экспонента
  while (mantissa >= 10) {
    mantissa /= 10;
    exponent++;
  }
  while (mantissa < 1) {
    mantissa *= 10;
    exponent--;
  }
  char exponent_sign = (exponent >= 0) ? '+' : '-';

  // полученные значения преобразуем в строки
  char *mantissa_str = double_to_str(mantissa, options);
  char *exponent_str = exp_int_to_str(exponent);

  // выделяем память для записи в 1 результирующую строку
  s21_size_t result_str_len = s21_strlen(prefix) + s21_strlen(mantissa_str) +
                              s21_strlen(exponent_str) + (sizeof(char) * 4);
  result_str = (char *)malloc(result_str_len);
  if (result_str == s21_NULL) {
    options.has_error = true;
    return s21_NULL;
  }

  for (s21_size_t i = 0; i < result_str_len; i++) result_str[i] = '\0';

  char *result_str_ptr = result_str;

  // объединяем префикс, мантиссу и экспоненту в результирующую строку
  s21_strncat(result_str_ptr, prefix, s21_strlen(prefix));
  s21_strncat(result_str_ptr, mantissa_str, s21_strlen(mantissa_str));
  while (*result_str_ptr != '\0') result_str_ptr++;
  *result_str_ptr = options.has_big_E_character ? 'E' : 'e';
  result_str_ptr++;
  *result_str_ptr = exponent_sign;
  s21_strncat(result_str_ptr, exponent_str, s21_strlen(exponent_str));

  if (mantissa_str != s21_NULL) free(mantissa_str);
  if (exponent_str != s21_NULL) free(exponent_str);
  if (prefix != s21_NULL) free(prefix);

  return result_str;
}

// добавляет префикс к числу в зависимости от его знака и настроек опций
char *add_prefix(bool is_negative_value, Options options) {
  char *prefix = (char *)malloc(2 * sizeof(char));
  prefix[0] = '\0';
  prefix[1] = '\0';
  if (prefix == s21_NULL) return s21_NULL;

  if (is_negative_value) {
    prefix[0] = '-';
  } else if (options.show_plus)
    prefix[0] = '+';
  else if (options.blank_space)
    prefix[0] = ' ';
  prefix[1] = '\0';
  return prefix;
}

// создает пустую строку для заполнения пробелами или нулями в зависимости от
// ширины
char *make_empty_str(Options options, s21_size_t already_filled_length) {
  char empty = options.zero ? '0' : ' ';
  s21_size_t empty_str_len = 0;
  if ((s21_size_t)options.width_description > already_filled_length)
    empty_str_len =
        (s21_size_t)options.width_description - already_filled_length;

  char *str = (char *)malloc(empty_str_len + 1);
  if (str == s21_NULL) return s21_NULL;
  for (s21_size_t i = 0; i < empty_str_len; i++) str[i] = empty;
  str[empty_str_len] = '\0';

  return str;
}

// получает беззнаковое целое значение из списка аргументов в зависимости от
// опций
long double get_float_value(Options options, va_list args) {
  long double value;
  if (options.long_double)
    value = va_arg(args, long double);
  else if (options.long_opt)
    value = va_arg(args, double);
  else if (options.short_opt)
    value = (float)va_arg(args, double);
  else
    value = (float)va_arg(args, double);
  return value;
}

// получает целое значение из списка аргументов в зависимости от опций
long long get_int_value(Options options, va_list args) {
  long long value;
  if (options.long_opt)
    value = va_arg(args, long int);
  else if (options.short_opt)
    value = (short int)va_arg(args, int);
  else
    value = va_arg(args, int);
  return value;
}

// получает беззнаковое целое значение из списка аргументов в зависимости от
// опций
unsigned long long get_unsigned_int_value(Options options, va_list args) {
  unsigned long long value;
  if (options.long_opt)
    value = va_arg(args, unsigned long int);
  else if (options.short_opt)
    value = (unsigned short int)va_arg(args, int);
  else
    value = va_arg(args, unsigned int);
  return value;
}

// преобразует целое число экспоненты в строку
char *exp_int_to_str(int value) {
  if (value < 0) value *= -1;

  char *str = (char *)malloc(sizeof(char) * 3);
  if (str == s21_NULL) return s21_NULL;

  s21_memset(str, '0', 2);
  str[2] = '\0';

  int i = 1;
  while (value != 0) {
    str[i--] = (value % 10) + '0';
    value /= 10;
  }

  return str;
}

// преобразует беззнаковое целое число в строку шестнадцатеричного представления
char *uint_to_hex_str(unsigned long long value, bool uppercase) {
  const char *digits_lower = "0123456789abcdef";
  const char *digits_upper = "0123456789ABCDEF";
  const char *digits = uppercase ? digits_upper : digits_lower;

  unsigned long long temp = value;
  int hex_digits = 0;
  do {
    temp >>= 4;
    hex_digits++;
  } while (temp > 0);

  char *result = (char *)malloc(hex_digits + 1);
  if (result == s21_NULL) return s21_NULL;

  result[hex_digits] = '\0';

  for (int i = hex_digits - 1; i >= 0; i--) {
    result[i] = digits[value & 0xF];
    value >>= 4;
  }

  return result;
}

// проверяет, является ли символ спецификатором формата
bool is_specifier(char c) {
  bool result;
  switch (c) {
    case '%':
    case 'c':
    case 'd':
    case 'f':
    case 's':
    case 'u':
    case 'g':
    case 'G':
    case 'e':
    case 'E':
    case 'x':
    case 'X':
    case 'o':
    case 'p':
      result = true;
      break;
    default:
      result = false;
      break;
  }
  return result;
}

// возвращает абсолютное значение числа с плавающей точкой
long double fabsl(long double x) {
  if (x < 0.0L) {
    return -x;
  } else {
    return x;
  }
}

// пеерворачивает строку
void reverse_string(char *str) {
  if (str == NULL) return;

  int length = s21_strlen(str);
  for (int i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}

// MARK: parser
const char *parse_options(Options *options, const char *format, va_list args) {
  const char *next_format_ptr;

  while (is_option(*format)) {
    switch (*format) {
      case '-':
        options->left_justification = true;  // выравнивания по левому краю
        options->zero = false;  // отмена выравнивания нулями
        break;
      case '+':
        options->show_plus = true;  // отображение знака плюс
        options->blank_space = false;  // отмена пробела перед числом
        break;
      case ' ':
        if (!options->show_plus)
          options->blank_space = true;  // отображение пробела перед числом,
                                        // если знак плюс не установлен
        break;
      case '.':
        format++;
        if (*format == '*')
          options->precision_description =
              va_arg(args, int);  // получение точности из аргументов
        else
          format = get_precision(options,
                                 format);  // разбор точности из строки формата
        if (format == s21_NULL) return s21_NULL;
        break;
      case '*':
        options->width_description =
            va_arg(args, int);  // получение ширины из аргументов
        break;
      case '1' ... '9':
        next_format_ptr = format + 1;
        options->width_description =
            *format - '0';  // установка начальной ширины
        while (is_digit(*next_format_ptr)) {
          options->width_description *= 10;
          options->width_description +=
              (*next_format_ptr) - '0';  // разбор многозначной ширины
          next_format_ptr++;
          format++;
        }
        break;
      case 'h':
        options->long_opt = false;
        options->short_opt = true;  // установка флага короткого целого
        options->long_double = false;
        break;
      case 'l':
        options->long_opt = true;  // установка флага длинного целого
        options->short_opt = false;
        options->long_double = false;
        break;
      case 'L':
        options->long_opt = false;
        options->short_opt = false;
        options->long_double =
            true;  // установка флага длинного с плавающей точкой
        break;
      case '#':
        options->alternative_form = true;  // установка альтернативной формы
        break;
      case '0':
        if (!options->left_justification)
          options->zero = true;  // установка выравнивания нулями
        break;
      default:
        break;
    }
    format++;
  }
  return format;
}

// значения по умолчания для сруктуры опций
void set_default(Options *options) {
  options->left_justification = false;
  options->show_plus = false;
  options->blank_space = false;
  options->short_opt = false;
  options->long_opt = false;
  options->long_double = false;
  options->alternative_form = false;
  options->zero = false;
  options->width_description = 1;
  options->precision_description = 6;
  options->has_big_E_character = false;
  options->has_error = false;
  options->upper_case = false;
}

// разбирает точность из строки формата
const char *get_precision(Options *options, const char *format) {
  if (is_digit(*format))
    options->precision_description = *format - '0';
  else
    return s21_NULL;

  format++;
  if (is_digit(*format)) {
    int current_precision = options->precision_description;
    if ((current_precision <= 1) && (*format <= '5')) {
      options->precision_description =
          (current_precision * 10) + (*format - '0');
    } else
      return s21_NULL;
  } else {
    format--;
  }
  return format;
}

bool is_option(char c) {
  bool result;

  switch (c) {
    case '-':
    case '+':
    case ' ':
    case '.':
    case '*':
    case '0' ... '9':
    case 'h':
    case 'l':
    case 'L':
    case '#':
      result = true;
      break;
    default:
      result = false;
      break;
  }

  return result;
}

// ghjdthrf является ли символ цифрой
bool is_digit(char c) { return (c >= '0' && c <= '9'); }