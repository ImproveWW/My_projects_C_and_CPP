#include <stddef.h>

#include "../s21_string.h"

void s21_errnum_tostring(char *str, int num);
char *s21_strcat(char *dest, const char *src);

#ifdef __linux__
#define ERRORUNK "Unknown error "
static const char *error_list[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "Invalid argument",
    // примеры сообщений о траблах в Линукс
};

#elif __APPLE__
#define ERRORUNK "Unknown error: "
static const char *error_list[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "Invalid argument",
    // примеры сообщений о траблах в Линукс
};

#endif

char *s21_strerror(int errnum) {
  size_t error_count = sizeof(error_list) / sizeof(error_list[0]);
  static char unknown_error[64];

  if (errnum < 0 || (unsigned int)errnum >= error_count) {
    const char *unknown_prefix = ERRORUNK;
    char part2[33];
    s21_errnum_tostring(part2, errnum);

    unknown_error[0] = '\0';
    s21_strcat(unknown_error, unknown_prefix);
    s21_strcat(unknown_error, part2);

    return unknown_error;
  } else {
    return (char *)error_list[errnum];
  }
}

void s21_errnum_tostring(char *str, int num) {
  int i, rem, len = 0, n = num;

  if (num == 0) {
    str[len++] = '0';
  } else {
    if (num < 0) {
      num = -num;
      str[len++] = '-';
    }
    while (n != 0) {
      len++;
      n /= 10;
    }
    for (i = len - 1; i >= (str[0] == '-' ? 1 : 0); i--) {
      rem = num % 10;
      str[i] = rem + '0';
      num /= 10;
    }
  }
  str[len] = '\0';
}

char *s21_strcat(char *dest, const char *src) {
  char *dest_ptr = dest;

  while (*dest_ptr != '\0') {
    dest_ptr++;
  }

  while (*src != '\0') {
    *dest_ptr++ = *src++;
  }

  *dest_ptr = '\0';

  return dest;
}
