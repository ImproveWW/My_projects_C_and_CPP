#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define ERROR -1

#define s21_NULL (void *)(0)
typedef size_t s21_size_t;

// core
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
// additional core
int s21_strcmp(const char *str_1, const char *str_2);
char *s21_strcpy(char *dest, const char *src);

// advanced
int firstchar(const char *src, const char *totrim, int offset);
int lastchar(const char *src, const char *totrim, int offset);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);

/*sprintf*/

typedef struct Options {
  bool left_justification;  // '-'
  bool show_plus;           // '+'
  bool blank_space;         // ' '
  bool short_opt;           // 'h'
  bool long_opt;            // 'l'
  bool long_double;         // 'L'
  bool alternative_form;    // '#'
  bool zero;                // '0'
  int width_description;
  int precision_description;
  bool has_big_E_character;  // scientific notation with 'e' or 'E'.
  bool has_error;
  bool upper_case;
} Options;

int s21_sprintf(char *buffer, const char *format, ...);

// Specifiers func
char *switch_specifier(char *buffer, const char *format, va_list args,
                       Options options);
void process_c_specifier(char *buffer, va_list args, Options options);
void process_d_specifier(char *buffer, va_list args, Options options);
void process_f_specifier(char *buffer, va_list args, Options options);
void process_s_specifier(char *buffer, va_list args, Options options);
void process_u_specifier(char *buffer, va_list args, Options options);
void process_e_specifier(char *buffer, va_list args, Options options);
void process_g_specifier(char *buffer, va_list args, Options options);
void process_x_specifier(char *buffer, va_list args, Options options);
void process_p_specifier(char *buffer, va_list args, Options options);
void process_o_specifier(char *buffer, va_list args, Options options);

// Helpers

char *int_to_str(long long value);
char *double_to_str(long double value, Options options);
char *double_to_enotation(long double value, Options options);
char *add_prefix(bool is_negative_value, Options options);
char *make_empty_str(Options options, s21_size_t already_filled_length);
long double get_float_value(Options options, va_list args);
long long get_int_value(Options options, va_list args);
unsigned long long get_unsigned_int_value(Options options, va_list args);
char *exp_int_to_str(int value);
char *uint_to_hex_str(unsigned long long value, bool uppercase);

bool is_specifier(char c);
long double fabsl(long double x);
void reverse_string(char *str);
const char *parse_options(Options *options, const char *format, va_list args);
void set_default(Options *options);
const char *get_precision(Options *options, const char *format);
bool is_option(char c);
bool is_digit(char c);

#endif
