#include <check.h>

#include "s21_test.h"

START_TEST(add_0) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{214748488, 214748488, 214748488, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_add(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{124, 126, 125, 0}};
  s21_decimal a_decimal2 = {{4294967295, 0, 0, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal2, b_decimal2, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{125, 124, 126, 0}};
  s21_decimal a_decimal3 = {{0, 4294967295, 0, 0}};
  s21_decimal b_decimal3 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal3, b_decimal3, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);
}
END_TEST

START_TEST(add_1) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0x99E35D6E, 0x6CA630CA, 0xCF624DAD, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_2) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{214748488, 214748488, 214748488, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_add(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{124, 126, 125, 0}};
  s21_decimal a_decimal2 = {{4294967295, 0, 0, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal2, b_decimal2, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{125, 124, 126, 0}};
  s21_decimal a_decimal3 = {{0, 4294967295, 0, 0}};
  s21_decimal b_decimal3 = {{125, 125, 125, 0}};
  code = s21_add(a_decimal3, b_decimal3, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);
}
END_TEST

START_TEST(add_3) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0xE8C2D4C2, 0xE1725129, 0x0985A7F3, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output;
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(weird_normalize_behavior) {
  weird_normalize_behavior = weird_normalize_behavior;
  s21_decimal val_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal val_2 = {{12345, 0, 0, 5 << 15}};
  s21_decimal res = {0};
  s21_add(val_1, val_2, &res);

  s21_decimal val_1_test_2 = {{4294967295, 4294967295, 42949672, 0}};
  s21_decimal val_2_test_2 = {{12345, 0, 0, 5 << 15}};
  s21_decimal res_2 = {0};
  s21_add(val_1_test_2, val_2_test_2, &res_2);
}
END_TEST

START_TEST(add_4) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0x29CEC056, 0x8DB581DE, 0x65064497, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_5) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_6) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal y = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 2);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_7) {
  s21_decimal x = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_8) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0x02F8BB19, 0xECF08C3C, 0x46136FC1, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_9) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0x8BB73C89, 0x308AA456, 0x66D11F15, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_10) {
  s21_decimal x = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0, 1, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_11) {
  s21_decimal x = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_12) {
  s21_decimal x = {{8, 0, 0, 0x001C0000}};
  s21_decimal y = {{2, 0, 0, 0x001C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{10, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_13) {
  int true_res = 1;
  s21_decimal val1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal val2 = {{0x422BDB6F, 0xEA71081D, 0xFB7D9F9E, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_14) {
  int true_res = 1;
  s21_decimal val1 = {{0xBCA1FF4F, 0x87371DE0, 0xD78DBBFD, 0x00000000}};
  s21_decimal val2 = {{0x17C5B270, 0x1E5ADF3C, 0xC5A48DE8, 0x00000000}};
  s21_decimal val3 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_15) {
  s21_decimal x = {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00170000}};
  s21_decimal y = {{0x00000036, 0x00000000, 0x00000000, 0x00170000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x00000035, 0x00000001, 0x00000000, 0x00170000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_16) {
  s21_decimal x = {{0x00000005, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal y = {{0x00000005, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{0x0000000A, 0x00000000, 0x00000000, 0x001C0000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 3; i >= 0; i--) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_17) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_18) {
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_19) {
  s21_decimal x = {{3, 0, 0, 0x80000000}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_20) {
  s21_decimal x = {{3, 0, 0, 0}};
  s21_decimal y = {{2, 0, 0, 0x80000000}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_decimal res = {{1, 0, 0, 0}};
  ck_assert_int_eq(s21_add(x, y, &z), 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(z.bits[i], res.bits[i]);
  }
}
END_TEST

START_TEST(add_21) {
  int true_res = 0;
  s21_decimal val1 = {{0x14A1D0CE, 0x89BC108A, 0x17C39287, 0x00000000}};
  s21_decimal val2 = {{0x3CFDBF53, 0xB24F4A86, 0x921E04AD, 0x00000000}};
  s21_decimal val3 = {{0x519F9021, 0x3C0B5B10, 0xA9E19735, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(add_22) {
  int true_res = 0;
  s21_decimal val1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x10000}};
  s21_decimal val2 = {{1, 0, 0, 0x10000}};
  s21_decimal val3 = {{0x9999999a, 0x99999999, 0x19999999, 0}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_add(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_comparison_positives_int) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_negatives_int) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 31}};
  s21_decimal val_2 = {{0, 1, 0, 1 << 31}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_combine_int_1) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 31}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_combine_int_2) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{0, 1, 0, 1 << 31}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_float_int) {
  s21_decimal val_1 = {{123, 0, 0, 3 << 16}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_int_float) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{124, 0, 0, 1 << 16}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_positives_float_float) {
  s21_decimal val_1 = {{123, 0, 0, 1 << 16}};
  s21_decimal val_2 = {{124, 0, 0, 1 << 16}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_negatives_float_int) {
  s21_decimal val_1 = {{123, 0, 0, (1 << 31) + (3 << 16)}};
  s21_decimal val_2 = {{0, 1, 0, 0}};
  ck_assert(s21_is_less(val_2, val_1) == 0);
  ck_assert(s21_is_less(val_1, val_2) == 1);
  ck_assert(s21_is_greater(val_2, val_1) == 1);
  ck_assert(s21_is_greater(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[1] = 1;
  val_2.bits[0] = 123;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_negatives_int_float) {
  s21_decimal val_1 = {{123, 0, 0, 0}};
  s21_decimal val_2 = {{124, 0, 0, (1 << 31) + (3 << 16)}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_equal(val_2, val_1) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  ck_assert(s21_is_not_equal(val_2, val_1) == 1);
}
END_TEST

START_TEST(test_comparison_negatives_float_float) {
  s21_decimal val_1 = {{123, 0, 0, (1 << 31) + (3 << 16)}};
  s21_decimal val_2 = {{124, 0, 0, (1 << 31) + (3 << 16)}};
  ck_assert(s21_is_less(val_2, val_1) == 1);
  ck_assert(s21_is_less(val_1, val_2) == 0);
  ck_assert(s21_is_greater(val_2, val_1) == 0);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 0);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 0);
  ck_assert(s21_is_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_1, val_2) == 1);
  val_1.bits[0] = 124;
  ck_assert(s21_is_less_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_less_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_greater_or_equal(val_1, val_2) == 1);
  ck_assert(s21_is_greater_or_equal(val_2, val_1) == 1);
  ck_assert(s21_is_equal(val_1, val_2) == 1);
  ck_assert(s21_is_equal(val_2, val_1) == 1);
  ck_assert(s21_is_not_equal(val_1, val_2) == 0);
  ck_assert(s21_is_not_equal(val_2, val_1) == 0);
}
END_TEST

START_TEST(test_comparison_weird_cases) {
  s21_decimal val_1 = {{4294967295, 4294967295, 4294967295, 3 << 16}};
  s21_decimal val_2 = {{4294967295, 4294967295, 4294967295, 6 << 16}};
  ck_assert(s21_is_equal(val_1, val_2) == 0);
}
END_TEST

START_TEST(test_comparison_zero) {
  s21_decimal val_1 = {{0, 0, 0, 0}};
  s21_decimal val_2 = {{0, 0, 0, 1 << 31}};
  ck_assert(s21_is_equal(val_1, val_2) == 1);
}

START_TEST(test_comparison_test_greater_sub) {
  s21_decimal val_1 = {{5, 0, 0, 0x80000000}};
  s21_decimal val_2 = {{1, 0, 0, 0x80000000}};
  s21_negate(val_1, &val_1);
  s21_negate(val_2, &val_2);
  ck_assert(s21_is_greater(val_1, val_2) == 1);
}

START_TEST(test_comparison_no_exp) {
  s21_decimal val_1 = {{1, 2, 3, 0}};
  s21_decimal val_2 = {{3, 2, 1, 0}};
  ck_assert(s21_is_equal(val_1, val_2) == 0);
}

START_TEST(test_comparison_normalize) {
  s21_decimal val_1 = {{1230, 0, 0, 1 << 16}};
  s21_decimal val_2 = {{123, 0, 0, 0}};
  ck_assert(s21_is_equal(val_1, val_2) == 1);
}

START_TEST(test_convertors_positive_int) {
  int value = 15;
  s21_decimal decimal = {{0}};
  int res = 0;
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(value, res);
}
END_TEST

START_TEST(test_convertors_negatives_int) {
  int value = -15;
  s21_decimal decimal = {{0}};
  int res = 0;
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(value, res);
}
END_TEST

START_TEST(test_convertors_positive_float) {
  float value = 15.25;
  s21_decimal decimal = {{0}};
  float res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq_tol(value, res, 1e-6);
}
END_TEST

START_TEST(test_convertors_negatives_float) {
  float value = -15.25;
  s21_decimal decimal = {{0}};
  float res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq_tol(value, res, 1e-6);
}
END_TEST

START_TEST(test_convertors_positives_float_to_int) {
  float value = 15.25;
  s21_decimal decimal = {{0}};
  int res = value;
  int dec_res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &dec_res) == 0);
  ck_assert_int_eq(res, dec_res);
}
END_TEST

START_TEST(test_convertors_negatives_float_to_int) {
  float value = -15.25;
  s21_decimal decimal = {{0}};
  int res = value;
  int dec_res = 0;
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &dec_res) == 0);
  ck_assert_int_eq(res, dec_res);
}

START_TEST(test_convertors_zero_int) {
  int value = 0, res = 0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_int_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 0);
  ck_assert_int_eq(res, value);
}
END_TEST

START_TEST(test_convertors_zero_float) {
  float value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(res, value);
}
END_TEST

START_TEST(test_convertors_nan) {
  float value = S21_NAN;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_max) {
  float value = MAX_DECIMAL;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_min) {
  float value = MIN_DECIMAL;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 1);
}
END_TEST

START_TEST(test_convertors_zero_scale) {
  float value = 10.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(value, res);
}
END_TEST

START_TEST(test_convertors_int_max) {
  int value = 0;
  s21_decimal decimal = {{123, 1, 0, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_2) {
  int value = 0;
  s21_decimal decimal = {{123, 0, 1, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_3) {
  int value = 0;
  s21_decimal decimal = {{123, 1, 1, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_4) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 0}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_5) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 1 << 31}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 1);
}
END_TEST

START_TEST(test_convertors_int_max_6) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, 4 << 16}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 0);
}
END_TEST

START_TEST(test_convertors_int_max_7) {
  int value = 0;
  s21_decimal decimal = {{2147483655, 0, 0, (1 << 31) + (4 << 16)}};
  ck_assert(s21_from_decimal_to_int(decimal, &value) == 0);
}
END_TEST

START_TEST(test_convertors_zero) {
  float value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  ck_assert(s21_from_float_to_decimal(value, &decimal) == 0);
  ck_assert(s21_from_decimal_to_float(decimal, &res) == 0);
  ck_assert_ldouble_eq(res, value);
}
END_TEST

START_TEST(test_convertors_max_8) {
  s21_decimal decimal = {{4294967295, 100, 0, 1 << 16}};
  int res = 0;
  ck_assert(s21_from_decimal_to_int(decimal, &res) == 1);
}

START_TEST(div_0) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 10;
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 15);
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 123478698;
  s21_set_power(&value_2, 5);
  memset(&result, 0, sizeof(s21_decimal));
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 22);
  memset(&result, 0, sizeof(s21_decimal));
  memset(&value_1, 0, sizeof(s21_decimal));
  memset(&value_2, 0, sizeof(s21_decimal));
  value_1.bits[0] = 4294967294;
  value_1.bits[1] = 1;
  value_2.bits[0] = 2;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], 4294967295);
}
END_TEST

START_TEST(div_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], 750);
}
END_TEST

START_TEST(div_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 150;
  value_2.bits[0] = 0;

  int result1 = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result1, 3);
  set_sign(&value_2);
  ck_assert_uint_eq(result1, 3);
}
END_TEST

START_TEST(div_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 547;
  value_2.bits[0] = 5;
  test.bits[0] = 1094;
  set_sign(&value_2);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  int pow = s21_get_power(result);
  ck_assert_uint_eq(pow, 1);
  ck_assert_uint_eq(getSign(result), 1);
  s21_decimal value_3 = {{20}};
  s21_decimal value_4 = {{5}};
  set_sign(&value_4);
  test.bits[0] = 4;
  memset(&result, 0, sizeof(s21_decimal));
  s21_div(value_3, value_4, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(getSign(result), 1);
}
END_TEST

START_TEST(div_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 22;
  value_2.bits[0] = 7;
  test.bits[0] = 3297921316;
  test.bits[1] = 208949406;
  test.bits[2] = 1703746271;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  int pow = s21_get_power(result);
  ck_assert_uint_eq(pow, 28);
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 2;
  test.bits[0] = 4294967291;
  test.bits[1] = 4;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(s21_get_power(result), 1);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{3333388888}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  test.bits[0] = 1409956271;
  test.bits[1] = 4207;
  test.bits[2] = 0;
  s21_set_power(&value_1, 5);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 28);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{3333388888}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_2.bits[0] = 22647;
  test.bits[0] = 3777176791;
  test.bits[1] = 1197098455;
  test.bits[2] = 797913073;
  s21_set_power(&value_1, 5);
  s21_set_power(&value_2, 3);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 28);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  value_2.bits[2] = 4294967295;
  test.bits[0] = 1;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{291}};
  s21_decimal value_2 = {{123}};
  s21_decimal result = {0};
  s21_decimal test = {0};
  test.bits[0] = 425568406;
  test.bits[1] = 790584587;
  test.bits[2] = 1282531838;
  s21_set_power(&value_2, 28);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
}
END_TEST

START_TEST(div_10) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 4294967295;
  value_2.bits[1] = 4294967295;
  value_2.bits[2] = 4294967295;
  test.bits[0] = 1;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
}
END_TEST

START_TEST(div_11) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 5);
  int over = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(over, 1);
  set_sign(&value_1);
  set_sign(&value_2);
  ck_assert_uint_eq(over, 1);
}
END_TEST

START_TEST(div_12) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 2;
  s21_set_power(&value_2, 5);
  set_sign(&value_1);
  int over = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(over, 2);
  delete_sign(&value_1);
  set_sign(&value_2);
  ck_assert_uint_eq(over, 2);
}
END_TEST

START_TEST(div_13) {
  s21_decimal value_1 = {{745}};
  s21_decimal value_2 = {{1}};
  s21_decimal result = {0};
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], value_1.bits[0]);
  ck_assert_uint_eq(getSign(result), 0);
  memset(&result, 0, sizeof(s21_decimal));
  set_sign(&value_2);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], value_1.bits[0]);
  ck_assert_uint_eq(getSign(result), 1);
}
END_TEST

START_TEST(div_14) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 112;
  test.bits[0] = 1227133512;
  test.bits[1] = 2454267026;
  test.bits[2] = 3834792228;
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(result.bits[1], test.bits[1]);
  ck_assert_uint_eq(result.bits[2], test.bits[2]);
  ck_assert_uint_eq(s21_get_power(result), 2);
}
END_TEST

START_TEST(test_floor) {
  s21_decimal a = {{0x44ff0000, 0x67732363, 0x5ea68b9c, 0x000f0000}};
  s21_decimal res;
  s21_decimal expected = {{0x4accef76, 0x00001aa4, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_floor_negative) {
  float float_value = -11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_floor_big) {
  s21_decimal value = {{115, 1, 0, 1 << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{429496741, 0, 0, 0}};
  ck_assert(s21_floor(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_floor_big_negative) {
  s21_decimal a = {{0xc21f0000, 0x84e3bbf7, 0x723bc2fa, 0x00090000}};
  s21_decimal res;
  s21_decimal expected = {{0x2d459980, 0xeaa0fff5, 0x00000001, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_floor_exp) {
  float float_value = 1.15, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_floor_no_exp) {
  float float_value = 115.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = floorf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}

START_TEST(test_round_no_exp) {
  float float_value = 115.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}

START_TEST(test_truncate_no_exp) {
  float float_value = 115.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  int result = 0;
  s21_from_decimal_to_int(decimal, &result);
  int expected = float_value;
  ck_assert_int_eq(expected, result);
}

START_TEST(test_floor_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_truncate_int_no_exp) {
  int int_value = 115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_floor_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_truncate_int_no_exp_neg) {
  int int_value = -115, res = 0;
  s21_decimal decimal = {{0}};
  s21_from_int_to_decimal(int_value, &decimal);
  ck_assert(s21_floor(decimal, &decimal) == 0);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(int_value, res);
}

START_TEST(test_round) {
  float float_value = 11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_negative) {
  float float_value = -11.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_big) {
  s21_decimal value = {{115, 2, 0, 1 << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{858993471, 0, 0, 0}};
  ck_assert(s21_round(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_round_zero) {
  float float_value = 0.0, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_big_exp) {
  float float_value = 11.555, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_sub) {
  float float_value = 12.5, res = 0.0;
  s21_decimal decimal = {{0}};
  s21_from_float_to_decimal(float_value, &decimal);
  ck_assert(s21_round(decimal, &decimal) == 0);
  s21_from_decimal_to_float(decimal, &res);
  float_value = roundf(float_value);
  ck_assert_ldouble_eq(float_value, res);
}
END_TEST

START_TEST(test_round_sub_2) {
  s21_decimal a = {{0xf535e9f0, 0x000e5ab9, 0x00000000, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_negate_positive_int) {
  s21_decimal value = {{115, 0, 0, 0}};
  s21_decimal res = {{0}};
  ck_assert(s21_negate(value, &res) == 0);
  s21_decimal expected_decimal = {{115, 0, 0, 1 << 31}};
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_negate_negative_int) {
  s21_decimal value = {{115, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, 0}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_negate_positive_float) {
  s21_decimal value = {{115, 0, 0, 1 << 16}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, (1 << 31) + (1 << 16)}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_negate_negative_float) {
  s21_decimal value = {{115, 0, 0, (1 << 31) + (1 << 16)}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{115, 0, 0, 1 << 16}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_negate_zero) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{0, 0, 0, 1 << 31}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_negate_negative_zero) {
  s21_decimal value = {{0, 0, 0, 1 << 31}};
  s21_decimal res = {{0}};
  s21_decimal expected_decimal = {{0, 0, 0, 0}};
  ck_assert(s21_negate(value, &res) == 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(test_truncate) {
  s21_decimal value = {{1, 0, 0, 1 << 16}};
  s21_decimal expected_decimal = {{0}};
  ck_assert(s21_truncate(value, &value) == 0);
  ck_assert_int_eq(s21_is_equal(value, expected_decimal), true);
}
END_TEST

START_TEST(test_floor_exp_29) {
  s21_decimal value = {{1, 0, 0, 29 << 16}};
  ck_assert(s21_floor(value, &value) == 1);
}
END_TEST

START_TEST(test_round_exp_29) {
  s21_decimal value = {{1, 0, 0, 29 << 16}};
  ck_assert(s21_round(value, &value) == 1);
}
END_TEST

START_TEST(test_truncate_exp_29) {
  int true_res = 0;
  s21_decimal val1 = {{0xD8678BCF, 0x92404BBC, 0x2E86DAFB, 0x00000000}};
  s21_decimal result = {{0xD8678BCF, 0x92404BBC, 0x2E86DAFB, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_truncate(val1, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(result.bits[i], output.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(test_negate_exp_29) {
  s21_decimal a = {{0x23559a40, 0x00000002, 0x00000000, 0x000a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x23559a40, 0x00000002, 0x00000000, 0x800a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(mul_0) {
  srand(time(NULL));
  long long a = random_ll() / 2;
  long long b = random_ll() / 2;
  long long expected = a * b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  int code = s21_mul(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(mul_1) {
  srand(time(NULL));
  long long a = random_ll() / 2;
  long long b = random_ll() / 2;
  long long expected = (a * (-1)) * b;
  s21_decimal res = {0};
  s21_decimal expected_decimal = convert_ll_to_decimal(expected);
  s21_decimal a_decimal = convert_ll_to_decimal(a);
  setSignInt(1, &a_decimal);
  s21_decimal b_decimal = convert_ll_to_decimal(b);
  int code = s21_mul(a_decimal, b_decimal, &res);
  code = code;
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  expected = a * (b * (-1));
  expected_decimal = convert_ll_to_decimal(expected);
  setSignInt(0, &a_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  expected = (a * (-1)) * (b * (-1));
  expected_decimal = convert_ll_to_decimal(expected);
  setSignInt(1, &a_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);
}
END_TEST

START_TEST(mul_2) {
  srand(time(NULL));
  float a = random_float(0.00, 1000.99999);
  float b = random_float(0.00, 1000.99999);
  float expected = a * b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);

  int code = s21_mul(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(mul_3) {
  srand(time(NULL));
  float a = random_float(0.00, 1000.99999);
  float b = random_float(0.00, 1000.99999);
  float expected = (a * (-1)) * b;

  s21_decimal res = {0};
  s21_decimal expected_decimal = {0};
  s21_decimal a_decimal = {0};
  s21_decimal b_decimal = {0};
  s21_from_float_to_decimal(expected, &expected_decimal);
  s21_from_float_to_decimal(a, &a_decimal);
  s21_from_float_to_decimal(b, &b_decimal);
  setSignInt(1, &a_decimal);

  int code = s21_mul(a_decimal, b_decimal, &res);
  float got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = (a * (-1)) * (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);

  expected = a * (b * (-1));
  s21_from_float_to_decimal(expected, &expected_decimal);
  setSignInt(1, &b_decimal);
  setSignInt(0, &a_decimal);
  code = s21_mul(a_decimal, b_decimal, &res);
  got_float = 0;
  s21_from_decimal_to_float(res, &got_float);
  ck_assert_int_eq(code, 0);
  ck_assert_float_eq_tol(got_float, expected, 1e-06);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal res = {0};
  s21_decimal expected_decimal = {{0, 0, 0, 0}};
  s21_decimal a_decimal = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal = {{125, 125, 125, 0}};
  int code = s21_mul(a_decimal, b_decimal, &res);
  ck_assert_int_eq(code, 1);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal), true);

  s21_decimal expected_decimal2 = {{0, 0, 0, 0}};
  s21_decimal a_decimal2 = {{214748363, 214748363, 214748363, 0}};
  s21_decimal b_decimal2 = {{125, 125, 125, 0}};
  setSignInt(1, &a_decimal2);
  code = s21_mul(a_decimal2, b_decimal2, &res);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal2), true);

  s21_decimal expected_decimal3 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal a_decimal3 = {{4294967295, 0, 0, 0}};
  s21_decimal b_decimal3 = {{1, 1, 1, 0}};
  code = s21_mul(a_decimal3, b_decimal3, &res);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(s21_is_equal(res, expected_decimal3), true);

  s21_decimal a_decimal4 = {{4294967295, 0, 0, (1 << 16)}};
  s21_decimal b_decimal4 = {{2, 2, 10, 0}};
  code = s21_mul(a_decimal4, b_decimal4, &res);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 5;
  test.bits[0] = 4294967293;
  test.bits[1] = 4294967295;
  test.bits[2] = 2147483647;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 0);
  ck_assert_uint_eq(getSign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {0};
  value_1.bits[0] = 4294967295;
  value_2.bits[0] = 255;
  test.bits[0] = 4294967041;
  test.bits[1] = 254;
  s21_set_power(&value_2, 10);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_uint_eq(s21_get_power(result), 10);
  ck_assert_uint_eq(getSign(result), 0);
  ck_assert_uint_eq(res, 0);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  s21_set_power(&value_2, 1);
  set_sign(&value_2);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 15;
  s21_set_power(&value_2, 1);
  int res = s21_mul(value_1, value_2, &result);
  ck_assert_uint_eq(res, 1);
}
END_TEST

START_TEST(sub_0) {
  int true_res = 0;
  s21_decimal val1 = {{0x423F4FF8, 0xE0FC85D3, 0xB2374887, 0x000E0000}};
  s21_decimal val2 = {{0x8C07F180, 0x5AF1861D, 0x85F3F906, 0x000D0000}};
  s21_decimal val3 = {{0x0568031A, 0xC471DF22, 0x7421A4F8, 0x800D0000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_1) {
  int true_res = 0;
  s21_decimal val1 = {{0xB75D7072, 0x5A088A2C, 0x800C3DA5, 0x80020000}};
  s21_decimal val2 = {{0xFC0E6698, 0x6A06C83F, 0xC93B52CD, 0x00040000}};
  s21_decimal val3 = {{0xFF016C5A, 0xB9D0499D, 0x820F64DF, 0x80020000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_2) {
  int true_res = 0;
  s21_decimal val1 = {{0x7FACEC97, 0x0D139BBE, 0x5157185D, 0x00090000}};
  s21_decimal val2 = {{0x4443F944, 0xFF60AE28, 0x6F24EBD8, 0x80060000}};
  s21_decimal val3 = {{0x2B4E2170, 0x5CD4AAFC, 0x6F39BE8F, 0x00060000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_3) {
  int true_res = 0;
  s21_decimal val1 = {{0x119DDF8E, 0xF1C6E216, 0xA0D2A160, 0x80040000}};
  s21_decimal val2 = {{0x3D6C858A, 0x4BE2CEAC, 0xE968012A, 0x000B0000}};
  s21_decimal val3 = {{0xEBE6E019, 0x89016CD4, 0xA0D2A2E8, 0x80040000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_4) {
  int true_res = 0;
  s21_decimal val1 = {{0x35716284, 0x9DB4C6C4, 0x17554546, 0x001C0000}};
  s21_decimal val2 = {{0xD3149B77, 0x57D7E4CE, 0xC5D6C200, 0x80140000}};
  s21_decimal val3 = {{0xB603898A, 0x41FDE9B5, 0xC5D6C204, 0x00140000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_5) {
  int true_res = 0;
  s21_decimal val1 = {{0x81327C03, 0xAA15F441, 0x9CA1CCF0, 0x00060000}};
  s21_decimal val2 = {{0x90464DB5, 0x7F974DEB, 0x4B68236B, 0x00030000}};
  s21_decimal val3 = {{0x150269BE, 0x0AAF58AF, 0x4B400A62, 0x80030000}};
  s21_decimal output = {{0x000FFFF0, 0x0FFFFF00, 0x000FF000, 0x80000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_6) {
  int true_res = 0;
  s21_decimal val1 = {{3, 0, 0, 0x80000000}};
  s21_decimal val2 = {{5, 0, 0, 0x80000000}};
  s21_decimal val3 = {{2, 0, 0, 0x00000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

START_TEST(sub_7) {
  int true_res = 0;
  s21_decimal val1 = {{5, 0, 0, 0x80000000}};
  s21_decimal val2 = {{1, 0, 0, 0x80000000}};
  s21_decimal val3 = {{4, 0, 0, 0x80000000}};
  s21_decimal output = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_res = s21_sub(val1, val2, &output);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(output.bits[i], val3.bits[i]);
  ck_assert_int_eq(s21_res, true_res);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, add_0);
  tcase_add_test(tc1_1, add_1);
  tcase_add_test(tc1_1, add_2);
  tcase_add_test(tc1_1, add_3);
  tcase_add_test(tc1_1, weird_normalize_behavior);
  tcase_add_test(tc1_1, add_4);
  tcase_add_test(tc1_1, add_5);
  tcase_add_test(tc1_1, add_6);
  tcase_add_test(tc1_1, add_7);
  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_16);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  tcase_add_test(tc1_1, add_19);
  tcase_add_test(tc1_1, add_20);
  tcase_add_test(tc1_1, add_21);
  tcase_add_test(tc1_1, add_22);
  tcase_add_test(tc1_1, test_comparison_positives_int);
  tcase_add_test(tc1_1, test_comparison_negatives_int);
  tcase_add_test(tc1_1, test_comparison_combine_int_1);
  tcase_add_test(tc1_1, test_comparison_combine_int_2);
  tcase_add_test(tc1_1, test_comparison_positives_float_int);
  tcase_add_test(tc1_1, test_comparison_positives_int_float);
  tcase_add_test(tc1_1, test_comparison_positives_float_float);
  tcase_add_test(tc1_1, test_comparison_negatives_float_int);
  tcase_add_test(tc1_1, test_comparison_negatives_int_float);
  tcase_add_test(tc1_1, test_comparison_negatives_float_float);
  tcase_add_test(tc1_1, test_comparison_weird_cases);
  tcase_add_test(tc1_1, test_comparison_no_exp);
  tcase_add_test(tc1_1, test_comparison_zero);
  tcase_add_test(tc1_1, test_comparison_normalize);
  tcase_add_test(tc1_1, test_comparison_test_greater_sub);
  tcase_add_test(tc1_1, test_convertors_positive_int);
  tcase_add_test(tc1_1, test_convertors_negatives_int);
  tcase_add_test(tc1_1, test_convertors_positive_float);
  tcase_add_test(tc1_1, test_convertors_negatives_float);
  tcase_add_test(tc1_1, test_convertors_positives_float_to_int);
  tcase_add_test(tc1_1, test_convertors_negatives_float_to_int);
  tcase_add_test(tc1_1, test_convertors_zero_int);
  tcase_add_test(tc1_1, test_convertors_zero_float);
  tcase_add_test(tc1_1, test_convertors_nan);
  tcase_add_test(tc1_1, test_convertors_max);
  tcase_add_test(tc1_1, test_convertors_min);
  tcase_add_test(tc1_1, test_convertors_zero_scale);
  tcase_add_test(tc1_1, test_convertors_int_max);
  tcase_add_test(tc1_1, test_convertors_int_max_2);
  tcase_add_test(tc1_1, test_convertors_int_max_3);
  tcase_add_test(tc1_1, test_convertors_int_max_4);
  tcase_add_test(tc1_1, test_convertors_int_max_5);
  tcase_add_test(tc1_1, test_convertors_int_max_6);
  tcase_add_test(tc1_1, test_convertors_int_max_7);
  tcase_add_test(tc1_1, test_convertors_zero);
  tcase_add_test(tc1_1, test_convertors_max_8);
  tcase_add_test(tc1_1, div_0);
  tcase_add_test(tc1_1, div_1);
  tcase_add_test(tc1_1, div_2);
  tcase_add_test(tc1_1, div_3);
  tcase_add_test(tc1_1, div_4);
  tcase_add_test(tc1_1, div_5);
  tcase_add_test(tc1_1, div_6);
  tcase_add_test(tc1_1, div_7);
  tcase_add_test(tc1_1, div_8);
  tcase_add_test(tc1_1, div_9);
  tcase_add_test(tc1_1, div_10);
  tcase_add_test(tc1_1, div_11);
  tcase_add_test(tc1_1, div_12);
  tcase_add_test(tc1_1, div_13);
  tcase_add_test(tc1_1, div_14);
  tcase_add_test(tc1_1, test_floor);
  tcase_add_test(tc1_1, test_floor_negative);
  tcase_add_test(tc1_1, test_floor_big);
  tcase_add_test(tc1_1, test_floor_big_negative);
  tcase_add_test(tc1_1, test_floor_exp);
  tcase_add_test(tc1_1, test_floor_no_exp);
  tcase_add_test(tc1_1, test_round_no_exp);
  tcase_add_test(tc1_1, test_truncate_no_exp);
  tcase_add_test(tc1_1, test_floor_int_no_exp);
  tcase_add_test(tc1_1, test_round_int_no_exp);
  tcase_add_test(tc1_1, test_truncate_int_no_exp);
  tcase_add_test(tc1_1, test_floor_int_no_exp_neg);
  tcase_add_test(tc1_1, test_round_int_no_exp_neg);
  tcase_add_test(tc1_1, test_truncate_int_no_exp_neg);
  tcase_add_test(tc1_1, test_round);
  tcase_add_test(tc1_1, test_round_negative);
  tcase_add_test(tc1_1, test_round_big);
  tcase_add_test(tc1_1, test_round_zero);
  tcase_add_test(tc1_1, test_round_big_exp);
  tcase_add_test(tc1_1, test_round_sub);
  tcase_add_test(tc1_1, test_round_sub_2);
  tcase_add_test(tc1_1, test_negate_positive_int);
  tcase_add_test(tc1_1, test_negate_negative_int);
  tcase_add_test(tc1_1, test_negate_positive_float);
  tcase_add_test(tc1_1, test_negate_negative_float);
  tcase_add_test(tc1_1, test_negate_zero);
  tcase_add_test(tc1_1, test_negate_negative_zero);
  tcase_add_test(tc1_1, test_truncate);
  tcase_add_test(tc1_1, test_floor_exp_29);
  tcase_add_test(tc1_1, test_round_exp_29);
  tcase_add_test(tc1_1, test_truncate_exp_29);
  tcase_add_test(tc1_1, test_negate_exp_29);
  tcase_add_test(tc1_1, mul_0);  // s21_mul
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, sub_0);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
