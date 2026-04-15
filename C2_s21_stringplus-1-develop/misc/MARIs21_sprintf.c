#include "../s21_string.h"
#include <math.h>

int s21_sprintf(char *str, const char *format, ...) {
    va_list arg;
    const char *temp = str;
    va_start(arg, format);

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == '%') {  // Обработка %%
                *str = *format;
                str++;
            } else {
                char buffer[BUFFER_SIZE] = {0};
                parserParameters parameters = {0, 0, '\0', 0};

                // Парсинг ширины, точности и длины
                s21_parseWidth(&format, &parameters);
                s21_parsePrecision(&format, &parameters);
                s21_parseLength(&format, &parameters);

                s21_checkSpecifier(format, buffer, arg, parameters);
                s21_strncpy(str, buffer, s21_strlen(buffer));
                str += s21_strlen(buffer);
            }
        } else {
            *str = *format;
            str++;
        }
        format++;
    }
    va_end(arg);
    *str = '\0';

    return (int)(str - temp);  // Рассчитываем и возвращаем длину
}

// парсинг ширины поля
void s21_parseWidth(const char **format, parserParameters *parameters) {
    va_list arg;
    if (**format == '*') {
        parameters->width = va_arg(arg, int);
        (*format)++;
    } else if (s21_isdigit(**format)) {
        char widthBuffer[20] = {0};
        int i = 0;

        while (s21_isdigit(**format)) {
            widthBuffer[i++] = **format;
            (*format)++;
        }

        parameters->width = s21_atoi(widthBuffer);
    }
}

// парсинг точности
void s21_parsePrecision(const char **format, parserParameters *parameters) {
    va_list arg;
    if (**format == '.') {
        (*format)++;
        if (**format == '*') {
            parameters->precision = va_arg(arg, int);
            (*format)++;
        } else if (s21_isdigit(**format)) {
            char precisionBuffer[20] = {0};
            int i = 0;

            while (s21_isdigit(**format)) {
                precisionBuffer[i++] = **format;
                (*format)++;
            }

            parameters->precision = s21_atoi(precisionBuffer);
        } else {
            // Если точность не указана после '.', по умолчанию 0
            parameters->precision = 0;
        }
    }
}

// парсинг длины
void s21_parseLength(const char **format, parserParameters *parameters) {
    switch (**format) {
        case 'h':
        case 'l':
        case 'L':
            parameters->length = **format;
            (*format)++;
            break;
        default:
            break;
    }
}

// обработка спецификатора
void s21_checkSpecifier(const char *format, char *buffer, va_list arg, parserParameters parameters) {
    switch (*format) {
        case 'c':
            s21_processChar(buffer, arg);
            break;
        case 'd':
            s21_processInteger(buffer, arg, parameters);
            break;
        case 'i':
            s21_processInteger(buffer, arg, parameters);
            break;
        case 'u':
            s21_processUnsignedInteger(buffer, arg, parameters);
            break;
        case 'f':
            s21_processFloat(buffer, arg, parameters);
            break;
        case 'F':
            s21_processFloat(buffer, arg, parameters);
            break;
        case 'e':
            s21_processScientific(buffer, arg, parameters);
            break;
        case 'E':
            s21_processScientific(buffer, arg, parameters);
            break;
        case 'g':
            s21_processScientific(buffer, arg, parameters);
            break;
        case 'G':
            s21_processFloat(buffer, arg, parameters);
            break;
        case 's':
            s21_processString(buffer, arg, parameters);
            break;
        case 'x':
            s21_processHex(buffer, arg, parameters);
            break;
        case 'X':
            s21_processHex(buffer, arg, parameters);
            break;
        case 'o':
            s21_processOctal(buffer, arg, parameters);
            break;
        case 'p':
            s21_processPointer(buffer, arg, parameters);
            break;
        case '%':
            s21_processPercent(buffer);
            break;
        default:
            break;
    }
}

// обработка спецификатора %c
void s21_processChar(char *buffer, va_list arg) {
    char charValue = (char) va_arg(arg, int);
    s21_strncat(buffer, &charValue, 1);
}

// обработка спецификаторов %d и %i
void s21_processInteger(char *buffer, va_list arg, parserParameters parameters) {
    int intValue;
    if (parameters.length == 'h') {
        intValue = (short) va_arg(arg, int);
    } else if (parameters.length == 'l') {
        intValue = va_arg(arg, long);
    } else {
        intValue = va_arg(arg, int);
    }

    char intBuffer[20] = {0};
    s21_itoa(intValue, intBuffer);
    s21_applyFormat(buffer, intBuffer, parameters);
}

// обработка спецификаторов %u
void s21_processUnsignedInteger(char *buffer, va_list arg, parserParameters parameters) {
    unsigned int uintValue;
    if (parameters.length == 'h') {
        uintValue = (unsigned short) va_arg(arg, unsigned int);
    } else if (parameters.length == 'l') {
        uintValue = va_arg(arg, unsigned long);
    } else {
        uintValue = va_arg(arg, unsigned int);
    }

    char uintBuffer[20] = {0};
    s21_utoa(uintValue, uintBuffer);
    s21_applyFormat(buffer, uintBuffer, parameters);
}

// обработка спецификаторов %f и %F
void s21_processFloat(char *buffer, va_list arg, parserParameters parameters) {
    double doubleValue = va_arg(arg, double);
    s21_ftoa(doubleValue, buffer, parameters);
}

// обработка спецификаторов %e и %E
void s21_processScientific(char *buffer, va_list arg, parserParameters parameters) {
    double doubleValue = va_arg(arg, double);
    s21_scientific(doubleValue, buffer, parameters);
}

// обработка спецификатора %s
void s21_processString(char *buffer, va_list arg, parserParameters parameters) {
    char *stringValue = va_arg(arg, char *);
    s21_applyFormat(buffer, stringValue, parameters);
}

// обработка спецификаторов %x и %X
void s21_processHex(char *buffer, va_list arg, parserParameters parameters) {
    unsigned int uintValue = va_arg(arg, unsigned int);
    char hexBuffer[20] = {0};
    s21_utohex(uintValue, hexBuffer);
    s21_applyFormat(buffer, hexBuffer, parameters);
}

// обработка спецификатора %o
void s21_processOctal(char *buffer, va_list arg, parserParameters parameters) {
    unsigned int uintValue = va_arg(arg, unsigned int);
    char octalBuffer[20] = {0};
    s21_utooct(uintValue, octalBuffer);
    s21_applyFormat(buffer, octalBuffer, parameters);
}

// обработка спецификатора %p
void s21_processPointer(char *buffer, va_list arg, parserParameters parameters) {
    void *ptrValue = va_arg(arg, void *);
    char ptrBuffer[20] = {0};
    s21_ptoa(ptrValue, ptrBuffer);
    s21_applyFormat(buffer, ptrBuffer, parameters);
}

// обработка спецификатора %%
void s21_processPercent(char *buffer) {
    s21_strncat(buffer, "%", 1);
}

// применение форматирования ширины и точности к значению
void s21_applyFormat(char *buffer, const char *value, parserParameters parameters) {
    int valueLength = s21_strlen(value);
    int width = parameters.width;

    if (width > 0 && width > valueLength) {
        char paddingChar = ' ';
        if (parameters.leftJustify) {
            s21_strncpy(buffer, value, valueLength);
            s21_appendCharMultiple(buffer + valueLength, paddingChar, width - valueLength);
        } else {
            s21_appendCharMultiple(buffer, paddingChar, width - valueLength);
            s21_strncat(buffer, value, valueLength);
        }
    } else {
        s21_strncpy(buffer, value, valueLength);
    }
}

// добавление нескольких символов к строке
void s21_appendCharMultiple(char *buffer, char c, int count) {
    for (int i = 0; i < count; ++i) {
        *buffer++ = c;
    }
    *buffer = '\0';
}

// проверка является ли символ цифрой
int s21_isdigit(int c) {
    return c >= '0' && c <= '9';
}

// преобразование строки в целое число
int s21_atoi(const char *str) {
    int result = 0;
    while (*str && s21_isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

// преобразование целого числа в строку
void s21_itoa(int value, char *buffer) {
    char temp[20];
    int pos = 0;
    int isNegative = 0;

    if (value == 0) {
        temp[pos++] = '0';
        temp[pos] = '\0';
    }

    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    while (value) {
        temp[pos++] = (value % 10) + '0';
        value /= 10;
    }

    if (isNegative) {
        temp[pos++] = '-';
    }

    temp[pos] = '\0';

    // реверс строки
    int i;
    for (i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[i] = '\0';
}

// преобразование unsigned целого числа в строку
void s21_utoa(unsigned int value, char *buffer) {
    char temp[20];
    int pos = 0;

    if (value == 0) {
        temp[pos++] = '0';
        temp[pos] = '\0';
    }

    while (value) {
        temp[pos++] = (value % 10) + '0';
        value /= 10;
    }

    temp[pos] = '\0';

    // реверс строки
    int i;
    for (i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[i] = '\0';
}

// преобразование float в строку
void s21_ftoa(double value, char *buffer, parserParameters parameters) {
    int intPart = (int) value;
    double fracPart = value - (double) intPart;
    char intBuffer[20] = {0};
    char fracBuffer[20] = {0};
    s21_itoa(intPart, intBuffer);

    if (parameters.precision < 0) {
        parameters.precision = 6;  // короче устанавливаем 6 если точность не указана
    }

    // умножаем дробную часть на 10 в степени precision и округляем
    fracPart = round(fracPart * pow(10, parameters.precision));

    s21_itoa((int) fracPart, fracBuffer);

    // собираем строку вместе
    s21_strncpy(buffer, intBuffer, s21_strlen(intBuffer));
    s21_strncat(buffer, ".", 1);
    s21_strncat(buffer, fracBuffer, s21_strlen(fracBuffer));
}

// преобразование в научную нотацию
void s21_scientific(double value, char *buffer, parserParameters parameters) {
    int exponent = 0;
    while (fabs(value) >= 10.0) {
        value /= 10.0;
        exponent++;
    }
    while (fabs(value) < 1.0) {
        value *= 10.0;
        exponent--;
    }
    s21_ftoa(value, buffer, parameters);
    char expBuffer[10];
    sprintf(expBuffer, "e%d", exponent);
    s21_strncat(buffer, expBuffer, s21_strlen(expBuffer));
}

// преобразование указателя в строку
void s21_ptoa(void *value, char *buffer) {
    uintptr_t intValue = (uintptr_t) value;
    char temp[20];
    int pos = 0;

    if (intValue == 0) {
        temp[pos++] = '0';
        temp[pos] = '\0';
    }

    while (intValue) {
        int digit = intValue % 16;
        if (digit < 10) {
            temp[pos++] = digit + '0';
        } else {
            temp[pos++] = digit - 10 + 'a';
        }
        intValue /= 16;
    }

    temp[pos] = '\0';

    // реверс строки
    int i;
    for (i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[i] = '\0';
}

// преобразование unsigned целого числа в шестнадцатеричную строку
void s21_utohex(unsigned int value, char *buffer) {
    char temp[20];
    int pos = 0;

    if (value == 0) {
        temp[pos++] = '0';
        temp[pos] = '\0';
    }

    while (value) {
        int digit = value % 16;
        if (digit < 10) {
            temp[pos++] = digit + '0';
        } else {
            temp[pos++] = digit - 10 + 'a';
        }
        value /= 16;
    }

    temp[pos] = '\0';

    // реверс строки
    int i;
    for (i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[i] = '\0';
}

// преобразование unsigned целого числа в восьмеричную строку
void s21_utooct(unsigned int value, char *buffer) {
    char temp[20];
    int pos = 0;

    if (value == 0) {
        temp[pos++] = '0';
        temp[pos] = '\0';
    }

    while (value) {
        int digit = value % 8;
        temp[pos++] = digit + '0';
        value /= 8;
    }

    temp[pos] = '\0';

    // реверс строки
    int i;
    for (i = 0; i < pos; i++) {
        buffer[i] = temp[pos - 1 - i];
    }
    buffer[i] = '\0';
}