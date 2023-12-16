#include "s21_tests.h"

START_TEST(s21_from_decimal_to_float_test_default) {
  printf("---------------------------------------------\n");
  float expected = 4326421;
  s21_decimal dec;
  s21_from_float_to_decimal(expected, &dec);
  float real = 0;
  s21_from_decimal_to_float(dec, &real);
  printf("Input: 4326421\nReal output: %f\nExpected: %f\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_minus) {
  printf("---------------------------------------------\n");
  float expected = -4326421;
  s21_decimal dec;
  s21_from_int_to_decimal(expected, &dec);
  float real = 0;
  s21_from_decimal_to_float(dec, &real);
  printf("Input: -4326421\nReal output: %f\nExpected: %f\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_float) {
  printf("---------------------------------------------\n");
  float expected = -432.4134;
  s21_decimal dec = {{4324134, 0, 0, MINUS | (4 << 16)}};
  float real = 0;
  s21_from_decimal_to_float(dec, &real);
  printf("Input: -432.4134\nReal output: %f\nExpected: %f\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-5);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_small_float) {
  printf("---------------------------------------------\n");
  float expected = -0.00000001234567;
  s21_decimal dec = {{1234567, 0, 0, MINUS | (14 << 16)}};
  float real = 0;
  s21_from_decimal_to_float(dec, &real);
  printf("Input: -0.00000001234567\nReal output: %.14f\nExpected: %.14f\n",
         real, expected);
  printf(real - expected < 1e-14 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-14);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_big_float) {
  printf("---------------------------------------------\n");
  float expected = 123456700.0;
  s21_decimal dec;
  s21_from_float_to_decimal(expected, &dec);
  float real = 0;
  s21_from_decimal_to_float(dec, &real);
  printf("Input: 123456700\nReal output: %.14f\nExpected: %.14f\n", real,
         expected);
  printf(real - expected < 1e+2 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e+2);
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s = suite_create("from_decimal_to_float\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_default);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_minus);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_float);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_small_float);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_big_float);
  suite_add_tcase(s, tc_core);
  return s;
}