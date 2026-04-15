#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINUS 0x80000000
#define PLUS 0xFF0000


typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[6];
} s21_decimal_big;



#include "./comparison/s21_comparison.h"
#include "./auxiliary/s21_auxiliary.h"
#include "./convertors/s21_convertors.h"
#include "./etc/s21_etc.h"
#include "./arithmetic/s21_arithmetic.h"
#include "./tests/s21_test.h"




#endif
