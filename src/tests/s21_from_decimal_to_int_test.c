#include "s21_tests.h"

START_TEST(s21_from_decimal_to_int_test_default) {
  printf("---------------------------------------------\n");
  int expected = 4326421;
  s21_decimal dec;
  s21_from_int_to_decimal(expected, &dec);
  int real = 0;
  s21_from_decimal_to_int(dec, &real);
  printf("Input: 4326421\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_minus) {
  printf("---------------------------------------------\n");
  int expected = -4326421;
  s21_decimal dec;
  s21_from_int_to_decimal(expected, &dec);
  int real = 0;
  s21_from_decimal_to_int(dec, &real);
  printf("Input: -4326421\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_float) {
  printf("---------------------------------------------\n");
  float expected = -432.41;
  s21_decimal dec = {{43241, 0, 0, MINUS | (2 << 16)}};
  int real = 0;
  s21_from_decimal_to_int(dec, &real);
  printf("Input: -432.41\nReal output: %d\nExpected: %d\n", real,
         (int)expected);
  printf(real == (int)expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, (int)expected);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_small_float) {
  printf("---------------------------------------------\n");
  float expected = -0.9;
  s21_decimal dec;
  s21_from_float_to_decimal(expected, &dec);
  int real = 0;
  s21_from_decimal_to_int(dec, &real);
  printf("Input: -0.9\nReal output: %d\nExpected: %d\n", real, (int)expected);
  printf(real == (int)expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, (int)expected);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s = suite_create("from_decimal_to_int\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_decimal_to_int_test_default);
  tcase_add_test(tc_core, s21_from_decimal_to_int_test_minus);
  tcase_add_test(tc_core, s21_from_decimal_to_int_test_float);
  tcase_add_test(tc_core, s21_from_decimal_to_int_test_small_float);
  suite_add_tcase(s, tc_core);
  return s;
}
