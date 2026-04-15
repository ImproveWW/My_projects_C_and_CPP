#include <check.h>
// "TestsSpritf.check"
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(s21_sprintf_one_c) {
  char buffer1[100] = {'\0'};
  char buffer2[100] = {'\0'};
  int c_spec_test = sprintf(buffer1, "%c", 'a');
  int _c_spec_test = s21_sprintf(buffer2, "%c", 'a');
  int c_spec_test_2 = sprintf(buffer1, "%-10c", 'T');
  int _c_spec_test_2 = s21_sprintf(buffer2, "%-10c", 'T');
  int c_spec_test_3 = sprintf(buffer1, "%8c", 'g');
  int _c_spec_test_3 = s21_sprintf(buffer2, "%8c", 'g');
  int percent_spec_test = sprintf(buffer1, "%%");
  int _percent_spec_test = s21_sprintf(buffer2, "%%");
  ck_assert_int_eq(c_spec_test, _c_spec_test);
  ck_assert_int_eq(c_spec_test_2, _c_spec_test_2);
  ck_assert_int_eq(c_spec_test_3, _c_spec_test_3);
  ck_assert_int_eq(percent_spec_test, _percent_spec_test);
}
END_TEST

START_TEST(s21_sprintf_two_d) {
  char buffer1[100] = {'\0'};
  char buffer2[100] = {'\0'};
  int d_spec_test = sprintf(buffer1, "%hd", (short int)123);
  int _d_spec_test = s21_sprintf(buffer2, "%hd", (short int)123);
  int d_spec_test_2 = sprintf(buffer1, "%018d", 123);
  int _d_spec_test_2 = s21_sprintf(buffer2, "%018d", 123);
  int d_spec_test_3 = sprintf(buffer1, "%- 18d", 123);
  int _d_spec_test_3 = s21_sprintf(buffer2, "%- 18d", 123);
  int d_spec_test_4 = sprintf(buffer1, "%*d", 4, 10);
  int _d_spec_test_4 = s21_sprintf(buffer2, "%*d", 4, 10);
  int d_spec_test_5 = sprintf(buffer1, "%d", 4);
  int _d_spec_test_5 = s21_sprintf(buffer2, "%d", 4);
  int d_spec_test_6 = sprintf(buffer1, "%d", 0);
  int _d_spec_test_6 = s21_sprintf(buffer2, "%d", 0);
  ck_assert_int_eq(d_spec_test, _d_spec_test);
  ck_assert_int_eq(d_spec_test_2, _d_spec_test_2);
  ck_assert_int_eq(d_spec_test_3, _d_spec_test_3);
  ck_assert_int_eq(d_spec_test_4, _d_spec_test_4);
  ck_assert_int_eq(d_spec_test_5, _d_spec_test_5);
  ck_assert_int_eq(d_spec_test_6, _d_spec_test_6);
}
END_TEST

START_TEST(s21_sprintf_three_f) {
  char buffer1[1000] = {'\0'};
  char buffer2[1000] = {'\0'};
  int f_spec_test = sprintf(buffer1, "%f", (float)12);
  int _f_spec_test = s21_sprintf(buffer2, "%f", (float)12);
  int f_spec_test_2 = sprintf(buffer1, "%.0f", (float)12);
  int _f_spec_test_2 = s21_sprintf(buffer2, "%.0f", (float)12);
  int f_spec_test_3 = sprintf(buffer1, "%#.12f", (float)12);
  int _f_spec_test_3 = s21_sprintf(buffer2, "%#.12f", (float)12);
  int f_spec_test_4 = sprintf(buffer1, "%.*f", 4, 1000000.0);
  int _f_spec_test_4 = s21_sprintf(buffer2, "%.*f", 4, 1000000.0);
  ck_assert_int_eq(f_spec_test, _f_spec_test);
  ck_assert_int_eq(f_spec_test_2, _f_spec_test_2);
  ck_assert_int_eq(f_spec_test_3, _f_spec_test_3);
  ck_assert_int_eq(f_spec_test_4, _f_spec_test_4);
}
END_TEST

START_TEST(s21_sprintf_four_s) {
  char buffer1[100] = {'\0'};
  char buffer2[100] = {'\0'};
  int s_spec_test = sprintf(buffer1, "%10s", "asd");
  int _s_spec_test = s21_sprintf(buffer2, "%10s", "asd");
  int s_spec_test_2 = sprintf(buffer1, "%5s", "o_o");
  int _s_spec_test_2 = s21_sprintf(buffer2, "%5s", "o_o");
  int s_spec_test_3 = sprintf(buffer1, "%-10s", "  asd");
  int _s_spec_test_3 = s21_sprintf(buffer2, "%-10s", "  asd");
  ck_assert_int_eq(s_spec_test, _s_spec_test);
  ck_assert_int_eq(s_spec_test_2, _s_spec_test_2);
  ck_assert_int_eq(s_spec_test_3, _s_spec_test_3);
}
END_TEST

START_TEST(s21_sprintf_five_u) {
  char buffer1[100] = {'\0'};
  char buffer2[100] = {'\0'};
  int u_spec_test = sprintf(buffer1, "%10u", 123);
  int _u_spec_test = s21_sprintf(buffer2, "%10u", 123);
  int u_spec_test_2 = sprintf(buffer1, "%-10u", 123);
  int _u_spec_test_2 = s21_sprintf(buffer2, "%-10u", 123);
  int u_spec_test_3 = sprintf(buffer1, "%3u", 123);
  int _u_spec_test_3 = s21_sprintf(buffer2, "%3u", 123);
  ck_assert_int_eq(u_spec_test, _u_spec_test);
  ck_assert_int_eq(u_spec_test_2, _u_spec_test_2);
  ck_assert_int_eq(u_spec_test_3, _u_spec_test_3);
}
END_TEST

START_TEST(s21_sprintf_six_e) {
  char buffer1[1000] = {'\0'};
  char buffer2[1000] = {'\0'};
  int spec_e_double_test = sprintf(buffer1, "%.0e", -0.0123);
  int _spec_e_double_test = s21_sprintf(buffer2, "%.0e", -0.0123);
  int spec_e_double_test_2 = sprintf(buffer1, "%#.0e", (double)1);
  int _spec_e_double_test_2 = s21_sprintf(buffer2, "%#.0e", (double)1);
  int spec_e_double_test_3 =
      sprintf(buffer1, "%.0e %.2e", (double)1, (-0.0123));
  int _spec_e_double_test_3 =
      s21_sprintf(buffer2, "%.0e %.2e", (double)1, (-0.0123));
  int spec_e_double_test_4 = sprintf(buffer1, "%.0E", -0.0123);
  int _spec_e_double_test_4 = s21_sprintf(buffer2, "%.0E", -0.0123);
  int spec_e_double_test_5 = sprintf(buffer1, "%-.0e", -0.0123);
  int _spec_e_double_test_5 = s21_sprintf(buffer2, "%-.0e", -0.0123);
  int spec_e_double_test_6 = sprintf(buffer1, "%.0e", 1000.10);
  int _spec_e_double_test_6 = s21_sprintf(buffer2, "%.0e", 1000.10);

  ck_assert_int_eq(spec_e_double_test, _spec_e_double_test);
  ck_assert_int_eq(spec_e_double_test_2, _spec_e_double_test_2);
  ck_assert_int_eq(spec_e_double_test_3, _spec_e_double_test_3);
  ck_assert_int_eq(spec_e_double_test_4, _spec_e_double_test_4);
  ck_assert_int_eq(spec_e_double_test_5, _spec_e_double_test_5);
  ck_assert_int_eq(spec_e_double_test_6, _spec_e_double_test_6);
}
END_TEST

START_TEST(s21_sprintf_seven_x) {
  char buffer1[1000] = {'\0'};
  char buffer2[1000] = {'\0'};
  int spec_X_test = sprintf(buffer1, "%X", 1234678);
  int _spec_X_test = s21_sprintf(buffer2, "%X", 1234678);
  int spec_X_test_2 = sprintf(buffer1, "%6X", 1234678);
  int _spec_X_test_2 = s21_sprintf(buffer2, "%6X", 1234678);
  int spec_X_test_3 = sprintf(buffer1, "%-x", 1234678);
  int _spec_X_test_3 = s21_sprintf(buffer2, "%-x", 1234678);

  ck_assert_int_eq(spec_X_test, _spec_X_test);
  ck_assert_int_eq(spec_X_test_2, _spec_X_test_2);
  ck_assert_int_eq(spec_X_test_3, _spec_X_test_3);
}
END_TEST

START_TEST(s21_sprintf_eight_o) {
  char buffer1[1000] = {'\0'};
  char buffer2[1000] = {'\0'};
  int o_spec_test = sprintf(buffer1, "%o", 1234);
  int _o_spec_test = s21_sprintf(buffer2, "%o", 1234);
  int o_spec_test_2 = sprintf(buffer1, "%10o", 1234);
  int _o_spec_test_2 = s21_sprintf(buffer2, "%10o", 1234);
  int o_spec_test_3 = sprintf(buffer1, "%4o", 1234);
  int _o_spec_test_3 = s21_sprintf(buffer2, "%4o", 1234);
  int o_spec_test_4 = sprintf(buffer1, "%-10o", 1234);
  int _o_spec_test_4 = s21_sprintf(buffer2, "%-10o", 1234);
  ck_assert_int_eq(o_spec_test, _o_spec_test);
  ck_assert_int_eq(o_spec_test_2, _o_spec_test_2);
  ck_assert_int_eq(o_spec_test_3, _o_spec_test_3);
  ck_assert_int_eq(o_spec_test_4, _o_spec_test_4);
}
END_TEST

START_TEST(s21_sprintf_nine_g) {
  char buffer1[1000] = {'\0'};
  char buffer2[1000] = {'\0'};
  int g_spec_test = sprintf(buffer1, "%g", 12.123123);
  int _g_spec_test = s21_sprintf(buffer2, "%.4g", 12.123123);

  ck_assert_int_eq(g_spec_test, _g_spec_test);
}
END_TEST

START_TEST(s21_sprintf_ten_p) {
  char buffer1[100] = {'\0'};
  char buffer2[100] = {'\0'};
  int x = 1234567;
  void *ptr = &x;
  double y = 123.1234567;
  void *ptr2 = &y;
  int test1 = sprintf(buffer1, "%p", ptr);
  int _test1 = s21_sprintf(buffer2, "%p", ptr);
  int test2 = sprintf(buffer1, "%-20p", ptr2);
  int _test2 = s21_sprintf(buffer2, "%-20p", ptr2);

  ck_assert_int_eq(test1, _test1);
  ck_assert_int_eq(test2, _test2);
}
END_TEST

START_TEST(s21_sprintf_eleven_all) {
  char buffer1[1000] = {'\0'};
  int all_spec_test =
      sprintf(buffer1, "%% char %-10c uint %-10u float %-19f str %8s", '!', 123,
              12.123, "asd");
  int _all_spec_test =
      s21_sprintf(buffer1, "%% char %-10c uint %-10u float %-19f str %8s", '!',
                  123, 12.123, "asd");
  int type_Ldouble_test = sprintf(buffer1, "%Lf", (long double)10.12);
  int _type_Ldouble_test = s21_sprintf(buffer1, "%Lf", (long double)10.12);

  ck_assert_int_eq(all_spec_test, _all_spec_test);
  ck_assert_int_eq(type_Ldouble_test, _type_Ldouble_test);
}
END_TEST

START_TEST(s21_memchr_test) {
  char test1[] = "pib";
  char test2 = '4';
  char test3 = '7';
  char test4[] = "bipbip/\0";
  char test5[] = "h";
  char test6 = 'h';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test2, 6),
                    (unsigned long)memchr(test1, test2, 4));
  ck_assert_uint_eq((unsigned long)s21_memchr(test1, test3, 6),
                    (unsigned long)memchr(test1, test3, 4));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test6, 6),
                    (unsigned long)memchr(test4, test6, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test5, test7, 1),
                    (unsigned long)memchr(test5, test7, 1));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test8, 6),
                    (unsigned long)memchr(test4, test8, 6));
  ck_assert_uint_eq((unsigned long)s21_memchr(test4, test9, 6),
                    (unsigned long)memchr(test4, test9, 6));
}

END_TEST

START_TEST(s21_memcmp_test) {
  char str_3[100] = "davosdim";
  char str_4[100] = "alisa";
  int res_3 = memcmp(str_3, str_4, 5);
  int res_3_s21 = s21_memcmp(str_3, str_4, 5);
  ck_assert_int_eq(res_3, res_3_s21);

  char str_5[100] = "davosdim";
  char str_6[100] = "davosdim";
  int res_4 = memcmp(str_5, str_6, 8);
  int res_4_s21 = s21_memcmp(str_5, str_6, 8);
  ck_assert_int_eq(res_4, res_4_s21);

  char str_7[100] = "";
  char str_8[100] = "z";
  int res_5 = memcmp(str_7, str_8, 10);
  int res_5_s21 = s21_memcmp(str_7, str_8, 10);
  ck_assert_int_eq(res_5, res_5_s21);
}
END_TEST

START_TEST(s21_memcpy_test) {
  char str_9[100] = "pupupu";
  char dest_1[100] = "don";
  char dest_1_s21[100] = "don";
  memcpy(dest_1, str_9, 6);
  s21_memcpy(dest_1_s21, str_9, 6);
  ck_assert_str_eq(dest_1, dest_1_s21);

  char str_10[100] = "0";
  char dest_2[100] = "don";
  char dest_2_s21[100] = "don";
  memcpy(dest_2, str_10, 1);
  s21_memcpy(dest_2_s21, str_10, 1);
  ck_assert_pstr_eq(dest_2, dest_2_s21);

  char str_11[100];
  char dest_3[100];
  char dest_3_s21[100];
  int i = 0;
  for (i = 0; i < 100; i++) {
    dest_3_s21[i] = dest_3[i];
  }
  memcpy(dest_3, str_11, 1);
  s21_memcpy(dest_3_s21, str_11, 1);
  ck_assert_pstr_eq(dest_3, dest_3_s21);
}
END_TEST

START_TEST(s21_memset_test) {
  char str_12[100] = "hello";
  char str_1_21[100] = "hello";
  char simv_3 = '#';
  memset(str_12, simv_3, 3);
  s21_memset(str_1_21, simv_3, 3);
  ck_assert_str_eq(str_12, str_1_21);

  char str_13[100];
  char str_2_21[100];
  (void)str_13;
  (void)str_2_21;
  char simv_4 = '!';
  memset(str_12, simv_3, 5);
  s21_memset(str_1_21, simv_3, 5);
  ck_assert_pstr_eq(str_12, str_1_21);

  char str_14[100] = "davosdim_privet";
  char str_3_21[100] = "davosdim_privet";
  simv_4 = '#';
  memset(str_14, simv_4, 6);
  s21_memset(str_3_21, simv_4, 6);
  ck_assert_pstr_eq(str_14, str_3_21);
}
END_TEST

START_TEST(s21_strncat_test) {
  char str_15[100] = "lepton";
  char str_4_21[100] = "lepton";
  char str_16[100] = "winamp";
  strncat(str_15, str_16, 7);
  s21_strncat(str_4_21, str_16, 7);
  ck_assert_pstr_eq(str_15, str_4_21);

  char str_17[100] = "lepton";
  char str_5_21[100] = "lepton";
  char str_18[100] = "";
  strncat(str_17, str_18, 4);
  s21_strncat(str_5_21, str_18, 4);
  ck_assert_pstr_eq(str_17, str_5_21);

  char str_19[100] = "";
  char str_6_21[100] = "";
  char str_20[100] = "stop";
  strncat(str_19, str_20, 5);
  s21_strncat(str_6_21, str_20, 5);
  ck_assert_pstr_eq(str_19, str_6_21);
}
END_TEST

START_TEST(s21_strchr_test) {
  char str_20[100] = "roman";
  char simv_5 = 'o';
  char *res_6 = strchr(str_20, simv_5);
  char *res_6_s21 = s21_strchr(str_20, simv_5);
  ck_assert_pstr_eq(res_6, res_6_s21);

  char str_21[100] = "roman";
  char simv_6 = 'v';
  char *res_7 = strchr(str_21, simv_6);
  char *res_7_s21 = s21_strchr(str_21, simv_6);
  ck_assert_pstr_eq(res_7, res_7_s21);

  char str_22[100] = "";
  char simv_7 = 'v';
  char *res_8 = strchr(str_22, simv_7);
  char *res_8_s21 = s21_strchr(str_22, simv_7);
  ck_assert_pstr_eq(res_8, res_8_s21);
}
END_TEST

START_TEST(s21_strncmp_test) {
  char str_23[100] = "expresso";
  char str_24[100] = "espresso";
  int res_9 = strncmp(str_23, str_24, 4);
  int res_9_s21 = s21_strncmp(str_23, str_24, 4);
  ck_assert_int_eq(res_9, res_9_s21);

  char str_25[100] = "vsemprivet";
  char str_26[100] = "vsemprivetik";
  int res_10 = strncmp(str_25, str_26, 10);
  int res_10_s21 = s21_strncmp(str_25, str_26, 10);
  ck_assert_int_eq(res_10, res_10_s21);

  // char str_27[100] = "v";
  // char str_28[100] = "s";
  // int res_11 = strncmp(str_27, str_28, 10);
  // int res_11_s21 = s21_strncmp(str_27, str_28, 10);
  // ck_assert_int_eq(res_11, res_11_s21);
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str_29[100] = "vsem";
  char dest_4[100] = "cat";
  char dest_4_s21[100] = "cat";
  strncpy(dest_4, str_29, 4);
  s21_strncpy(dest_4_s21, str_29, 4);
  ck_assert_pstr_eq(dest_4, dest_4_s21);

  char str_30[100] = "j";
  char dest_5[100] = "kill";
  char dest_5_s21[100] = "kill";
  strncpy(dest_5, str_30, 1);
  s21_strncpy(dest_5_s21, str_30, 1);
  ck_assert_pstr_eq(dest_5, dest_5_s21);

  char str_31[100] = "";
  char dest_6[100] = "";
  char dest_6_s21[100] = "";

  int p = 0;
  for (p = 0; p; p++) {
    dest_6_s21[p] = dest_6[p];
  }
  strncpy(dest_6, str_31, 1);
  s21_strncpy(dest_6, str_31, 1);
  ck_assert_pstr_eq(dest_6, dest_6_s21);
}
END_TEST

START_TEST(s21_strcspn_test) {
  char str_32[100] = "privet_pir";
  char str_33[100] = "ty";
  int res_12 = strcspn(str_32, str_33);
  int res_12_s21 = s21_strcspn(str_32, str_33);
  ck_assert_int_eq(res_12, res_12_s21);

  char str_34[100] = "vbn";
  char str_35[100] = "hello";
  int res_13 = strcspn(str_34, str_35);
  int res_13_s21 = s21_strcspn(str_34, str_35);
  ck_assert_int_eq(res_13, res_13_s21);

  char str_36[100] = "hello";
  char str_37[100] = "";
  int res_14 = strcspn(str_36, str_37);
  int res_14_s21 = s21_strcspn(str_36, str_37);
  ck_assert_int_eq(res_14, res_14_s21);
}
END_TEST

START_TEST(s21_strerror_test) {
#ifdef __APPLE__
  int tests = 108;
#elif __linux__
  int tests = 134;
#endif
  for (int i = 0; i < tests; i++) {
    char *str_38 = strerror(tests);
    char *str_39 = s21_strerror(tests);
    ck_assert_str_eq(str_38, str_39);
  }
}
END_TEST

START_TEST(s21_strlen_test) {
  char str_40[100] = "pererabotka";
  int res_15 = strlen(str_40);
  int res_15_s21 = s21_strlen(str_40);
  ck_assert_int_eq(res_15, res_15_s21);

  char str_41[100] = "perer/0abotka";
  int res_16 = strlen(str_41);
  int res_16_s21 = s21_strlen(str_41);
  ck_assert_int_eq(res_16, res_16_s21);

  char str_42[100] = "";
  int res_17 = strlen(str_42);
  int res_17_s21 = s21_strlen(str_42);
  ck_assert_int_eq(res_17, res_17_s21);
}
END_TEST

START_TEST(s21_strpbrk_test) {
  char str43[100] = "stroka";
  char str44[100] = "pila";
  char *res_18 = strpbrk(str43, str44);
  char *res_18_s21 = strpbrk(str43, str44);
  ck_assert_str_eq(res_18, res_18_s21);

  char str_45[100] = "vsem privet";
  char str_46[100] = "k;\0";
  char *res_19 = strpbrk(str_45, str_46);
  char *res_19_s21 = s21_strpbrk(str_45, str_46);
  ck_assert_ptr_eq(res_19, res_19_s21);

  char str_47[100] = "";
  char str_48[100] = "\0";
  char *res_20 = strpbrk(str_47, str_48);
  char *res_20_s21 = s21_strpbrk(str_47, str_48);
  ck_assert_ptr_eq(res_20, res_20_s21);
}
END_TEST

START_TEST(s21_strrchr_test) {
  char str_49[100] = "hello";
  char chr_50 = 'l';
  char *res_21 = strrchr(str_49, chr_50);
  char *res_21_s21 = s21_strrchr(str_49, chr_50);
  ck_assert_str_eq(res_21, res_21_s21);

  char str_51[100] = "privet";
  char chr_52 = 's';
  char *res_22 = strrchr(str_51, chr_52);
  char *res_22_s21 = s21_strrchr(str_51, chr_52);
  ck_assert_int_eq(res_22 == NULL, res_22_s21 == NULL);

  char str_53[100] = "";
  char chr_54 = 'b';
  char *res_23 = strrchr(str_53, chr_54);
  char *res_23_s21 = s21_strrchr(str_53, chr_54);
  ck_assert_int_eq(res_23 == NULL, res_23_s21 == NULL);
}
END_TEST

START_TEST(s21_strstr_test) {
  char str_55[100] = "pivo i kvas";
  char str_56[100] = "i ";
  char *res_24 = strstr(str_55, str_56);
  char *res_24_s21 = s21_strstr(str_55, str_56);
  ck_assert_str_eq(res_24, res_24_s21);

  char str_57[100] = "vsem\0privet";
  char str_58[100] = "privet";
  char *res_25 = strstr(str_57, str_58);
  char *res_25_s21 = s21_strstr(str_57, str_58);
  ck_assert_int_eq(res_25 == NULL, res_25_s21 == NULL);

  char str_99[100] = "";
  char str_100[100] = "wow";
  char *res_26 = strstr(str_99, str_100);
  char *res_26_s21 = s21_strstr(str_99, str_100);
  ck_assert_int_eq(res_26 == NULL, res_26_s21 == NULL);
}
END_TEST
START_TEST(s21_strtok_test) {
  char str_59[100] = "bell-like-";
  char str_60[100] = "-";
  char *res_27 = strtok(str_59, str_60);
  char *res_27_s21 = s21_strtok(str_59, str_60);
  ck_assert_str_eq(res_27, res_27_s21);

  char str_61[100] = "hell";
  char str_62[100] = "-";
  char *res_28 = strtok(str_61, str_62);
  char *res_28_s21 = s21_strtok(str_61, str_62);
  ck_assert_int_eq(res_28 == NULL, res_28_s21 == NULL);

  char *str_63 = NULL;
  char str_64[100] = "-";
  char *res_29 = strtok(str_63, str_64);
  char *res_29_s21 = s21_strtok(str_63, str_64);
  ck_assert_int_eq(res_29 == NULL, res_29_s21 == NULL);
}
END_TEST

START_TEST(s21_to_upper_test) {
  char str_65[100] = "AlaSka";
  char *res_30 = "ALASKA";
  char *res_30_s21 = s21_to_upper(str_65);
  ck_assert_str_eq(res_30, res_30_s21);

  char str_66[100] = "KARELIA";
  char *res_31 = "KARELIA";
  char *res_31_s21 = s21_to_upper(str_66);
  ck_assert_str_eq(res_31, res_31_s21);

  char *str_67 = NULL;
  char *res_32 = NULL;
  char *res_32_s21 = s21_to_upper(str_67);
  ck_assert_int_eq(res_32 == NULL, res_32_s21 == NULL);
}
END_TEST

START_TEST(s21_insert_test) {
  char str_68[100] = "capital of Sakhalin Island ";
  char str_69[100] = "Yuzhno-Sakhalinsk";
  char *res_33 = "capital of Sakhalin Island Yuzhno-Sakhalinsk";
  char *res_33_s21 = s21_insert(str_68, str_69, 27);
  ck_assert_str_eq(res_33, res_33_s21);
  free(res_33_s21);
  char str_70[100] = "bonnie and clyde";
  // char *res_34 = NULL;
  char *res_34_s21 = s21_insert(str_70, "!!!!!", 25);
  ck_assert(res_34_s21 == s21_NULL);
  free(res_34_s21);

  char *str_72 = NULL;
  char *str_73 = "b";
  char *res_35 = NULL;
  char *res_35_s21 = s21_insert(str_72, str_73, 1);
  ck_assert_int_eq(res_35 == NULL, res_35_s21 == NULL);
  free(res_35_s21);
}
END_TEST

START_TEST(s21_trim_test) {
  char *trimmed_str;
  char *str_to_trim = " \n   Hello, world!  !\n";
  trimmed_str = s21_trim(str_to_trim, " H!\nd");
  if (trimmed_str) {
    ck_assert_str_eq(trimmed_str, "ello, worl");
    free(trimmed_str);
  }

  char str_76[100] = "fjord";
  char str_77[100] = "!!";
  char *res_37 = "fjord";
  char *res_37_s21 = s21_trim(str_76, str_77);
  ck_assert_str_eq(res_37, res_37_s21);

  char *str_78 = NULL;
  char *str_79 = "c";
  char *res_38 = NULL;
  char *res_38_s21 = s21_trim(str_78, str_79);
  ck_assert_int_eq(res_38 == NULL, res_38_s21 == NULL);
}
END_TEST

START_TEST(s21_to_lower_test) {
  char str_80[100] = "BEEr test";
  char *res_39 = "beer test";
  char *res_39_s21 = s21_to_lower(str_80);
  ck_assert_str_eq(res_39, res_39_s21);
  free(res_39_s21);
  char str_81[100] = "reallybeertest";
  char *res_40 = "reallybeertest";
  char *res_40_s21 = s21_to_lower(str_81);
  ck_assert_str_eq(res_40, res_40_s21);
  free(res_40_s21);

  char *str_101 = NULL;
  char *res_41 = NULL;
  char *res_41_s21 = s21_to_lower(str_101);
  ck_assert_int_eq(res_41 == NULL, res_41_s21 == NULL);
  free(res_41_s21);
}
END_TEST

START_TEST(test_null_string) {
  char *token = s21_strtok(NULL, ",");
  ck_assert_msg(token == NULL, "Token should be NULL for NULL string input");
}
END_TEST

START_TEST(test_empty_string) {
  char *token = s21_strtok("", ",");
  ck_assert_msg(token == NULL,
                "Token should be NULL for an empty string with a delimiter");
}
END_TEST

START_TEST(test_no_delimiters) {
  char str[] = "HelloWorld";
  char *token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "HelloWorld");
}
END_TEST

START_TEST(test_delimiters_at_beginning) {
  char str[] = ",apple,orange";
  char *token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "apple");
}
END_TEST

START_TEST(test_delimiters_at_end) {
  char str[] = "apple,orange,";
  char *token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "apple");
}
END_TEST

START_TEST(test_multiple_delimiters_between_tokens) {
  char str[] = "apple,,orange,,banana";
  char *token = s21_strtok(str, ",");
  ck_assert_str_eq(token, "apple");
}
END_TEST
START_TEST(test_s21_memchr_null_input) {
  ck_assert_ptr_eq(s21_memchr(NULL, 'a', 10), NULL);
}
END_TEST

START_TEST(test_s21_memchr_empty_string) {
  char str[10] = {0};
  ck_assert_ptr_eq(s21_memchr(str, 'a', 10), NULL);
}
END_TEST

START_TEST(test_s21_memchr_character_not_found) {
  char str[10] = "abcdefghi";
  ck_assert_ptr_eq(s21_memchr(str, 'z', 10), NULL);
}
END_TEST

START_TEST(test_s21_memchr_character_found) {
  char str[10] = "abcdefghi";
  ck_assert_ptr_eq(s21_memchr(str, 'c', 10), str + 2);
}
END_TEST
START_TEST(test_s21_strerror) {
  // Test case 1: errnum within the error list range
  ck_assert_str_eq(s21_strerror(0), "Success");
  ck_assert_str_eq(s21_strerror(1), "Operation not permitted");
  ck_assert_str_eq(s21_strerror(10), "Invalid argument");
}
END_TEST

// Test case for NULL buffer or format
START_TEST(test_null_buffer_or_format) {
  char *buffer = NULL;
  const char *format = NULL;
  int result = s21_sprintf(buffer, format);
  ck_assert_int_eq(result, -1);
}
END_TEST

// Test case for empty format
START_TEST(test_empty_format) {
  char buffer[100] = {0};
  const char *format = "";
  int result = s21_sprintf(buffer, format);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Test case for non-format specifiers
START_TEST(test_non_format_specifiers) {
  char buffer[100] = {0};
  const char *format = "Hello, World!";
  int result = s21_sprintf(buffer, format);
  ck_assert_int_eq(result, strlen(format));
  ck_assert_str_eq(buffer, format);
}
END_TEST

// Test case for a single format specifier
START_TEST(test_single_format_specifier) {
  char buffer[100] = {0};
  const char *format = "%d";
  int value = 42;
  int result = s21_sprintf(buffer, format, value);
  char expected[100] = {0};
  snprintf(expected, sizeof(expected), format, value);
  ck_assert_int_eq(result, strlen(expected));
  ck_assert_str_eq(buffer, expected);
}
END_TEST

// Test case for multiple format specifiers
START_TEST(test_multiple_format_specifiers) {
  char buffer[100] = {0};
  const char *format = "%d %s";
  int value = 42;
  const char *str = "Hello";
  int result = s21_sprintf(buffer, format, value, str);
  char expected[100] = {0};
  snprintf(expected, sizeof(expected), format, value, str);
  ck_assert_int_eq(result, strlen(expected));
  ck_assert_str_eq(buffer, expected);
}
END_TEST

// Test case for invalid format specifier
START_TEST(test_invalid_format_specifier) {
  char buffer[100] = {0};
  const char *format = "%z";
  int result = s21_sprintf(buffer, format);
  ck_assert_int_eq(result, -1);
}
END_TEST

// Test case for format specifier with invalid option
START_TEST(test_format_specifier_with_invalid_option) {
  char buffer[100] = {0};
  const char *format = "%-z";
  int result = s21_sprintf(buffer, format);
  ck_assert_int_eq(result, -1);
}
END_TEST
// Test case for format specifier with valid option
START_TEST(test_format_specifier_with_valid_option) {
  char buffer[100] = {0};
  const char *format = "%10d";
  int value = 42;
  int result = s21_sprintf(buffer, format, value);
  char expected[100] = {0};
  snprintf(expected, sizeof(expected), format, value);
  ck_assert_int_eq(result, strlen(expected));
  ck_assert_str_eq(buffer, expected);
}
END_TEST
int main() {
  Suite *Suite1 = suite_create("s21_stringPlus");
  TCase *TestCase1 = tcase_create("s21_string");
  SRunner *SuiteRun = srunner_create(Suite1);
  suite_add_tcase(Suite1, TestCase1);

  tcase_add_test(TestCase1, test_null_buffer_or_format);
  tcase_add_test(TestCase1, test_empty_format);
  tcase_add_test(TestCase1, test_non_format_specifiers);
  tcase_add_test(TestCase1, test_single_format_specifier);
  tcase_add_test(TestCase1, test_multiple_format_specifiers);
  tcase_add_test(TestCase1, test_invalid_format_specifier);
  tcase_add_test(TestCase1, test_format_specifier_with_invalid_option);
  tcase_add_test(TestCase1, test_format_specifier_with_valid_option);
  tcase_add_test(TestCase1, test_s21_strerror);
  tcase_add_test(TestCase1, test_s21_memchr_null_input);
  tcase_add_test(TestCase1, test_s21_memchr_empty_string);
  tcase_add_test(TestCase1, test_s21_memchr_character_not_found);
  tcase_add_test(TestCase1, test_s21_memchr_character_found);
  tcase_add_test(TestCase1, test_null_string);
  tcase_add_test(TestCase1, test_empty_string);
  tcase_add_test(TestCase1, test_no_delimiters);
  tcase_add_test(TestCase1, test_delimiters_at_beginning);
  tcase_add_test(TestCase1, test_delimiters_at_end);
  tcase_add_test(TestCase1, test_multiple_delimiters_between_tokens);
  tcase_add_test(TestCase1, s21_sprintf_one_c);
  tcase_add_test(TestCase1, s21_sprintf_two_d);
  tcase_add_test(TestCase1, s21_sprintf_three_f);
  tcase_add_test(TestCase1, s21_sprintf_four_s);
  tcase_add_test(TestCase1, s21_sprintf_five_u);
  tcase_add_test(TestCase1, s21_sprintf_six_e);
  tcase_add_test(TestCase1, s21_sprintf_seven_x);
  tcase_add_test(TestCase1, s21_sprintf_eight_o);
  tcase_add_test(TestCase1, s21_sprintf_nine_g);
  tcase_add_test(TestCase1, s21_sprintf_ten_p);
  tcase_add_test(TestCase1, s21_sprintf_eleven_all);
  tcase_add_test(TestCase1, s21_memchr_test);
  tcase_add_test(TestCase1, s21_memcmp_test);
  tcase_add_test(TestCase1, s21_memcpy_test);
  tcase_add_test(TestCase1, s21_memset_test);
  tcase_add_test(TestCase1, s21_strncat_test);
  tcase_add_test(TestCase1, s21_strchr_test);
  tcase_add_test(TestCase1, s21_strncmp_test);
  tcase_add_test(TestCase1, s21_strncpy_test);
  tcase_add_test(TestCase1, s21_strcspn_test);
  tcase_add_test(TestCase1, s21_strerror_test);
  tcase_add_test(TestCase1, s21_strlen_test);
  tcase_add_test(TestCase1, s21_strpbrk_test);
  tcase_add_test(TestCase1, s21_strrchr_test);
  tcase_add_test(TestCase1, s21_strstr_test);
  tcase_add_test(TestCase1, s21_strtok_test);
  tcase_add_test(TestCase1, s21_to_upper_test);
  tcase_add_test(TestCase1, s21_to_lower_test);
  tcase_add_test(TestCase1, s21_insert_test);
  tcase_add_test(TestCase1, s21_trim_test);

  srunner_run_all(SuiteRun, CK_NORMAL);
  int fails = srunner_ntests_failed(SuiteRun);
  srunner_free(SuiteRun);
  return fails;
}
