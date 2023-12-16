#include "s21_tests.h"

START_TEST(s21_from_float_to_decimal_test_nan) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  float num = 0.0 / 0.0;
  int real = s21_from_float_to_decimal(num, dst);
  free(dst);
  int expected = 1;
  printf("Input: 0.0/0.0\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_too_small) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  float num = 1e-29;
  int real = s21_from_float_to_decimal(num, dst);
  free(dst);
  int expected = 1;
  printf("Input: 1e-29\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_default_small) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  float num = 0.0000000023456788;
  int expected_error = 0;
  int real_error = s21_from_float_to_decimal(num, dst);
  unsigned int expected_mantissa = 2345679;
  unsigned int real_mantissa = dst->bits[0];
  unsigned int expected_exp = 15;
  unsigned int real_exp = dst->bits[3] >> 16;
  printf("Input: 0.0000000023456788\n");
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "mantissa:%d\nreal "
      "mantissa:%d\nexpected exp:%d\nreal exp:%d\n",
      expected_error, real_error, expected_mantissa, real_mantissa,
      expected_exp, real_exp);

  printf((real_mantissa == expected_mantissa && real_exp == expected_exp &&
          expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real_error, expected_error);
  ck_assert_int_eq(real_mantissa, expected_mantissa);
  ck_assert_int_eq(real_exp, expected_exp);
  free(dst);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_default_avg) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  float num = 5676.1236;
  int expected_error = 0;
  int real_error = s21_from_float_to_decimal(num, dst);
  unsigned int expected_mantissa = 5676124;
  unsigned int real_mantissa = dst->bits[0];
  unsigned int expected_exp = 3;
  unsigned int real_exp = dst->bits[3] >> 16;
  printf("Input: 5676.1236\n");
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "mantissa:%d\nreal "
      "mantissa:%d\nexpected exp:%d\nreal exp:%d\n",
      expected_error, real_error, expected_mantissa, real_mantissa,
      expected_exp, real_exp);

  printf((real_mantissa == expected_mantissa && real_exp == expected_exp &&
          expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real_error, expected_error);
  ck_assert_int_eq(real_mantissa, expected_mantissa);
  ck_assert_int_eq(real_exp, expected_exp);
  free(dst);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_default_big) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  float num = 1234567099.5444;
  int expected_error = 0;
  int real_error = s21_from_float_to_decimal(num, dst);
  unsigned int expected_mantissa = 1234567000;
  unsigned int real_mantissa = dst->bits[0];
  unsigned int expected_exp = 0;
  unsigned int real_exp = dst->bits[3] >> 16;
  printf("Input: 5676.1236\n");
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "mantissa:%d\nreal "
      "mantissa:%d\nexpected exp:%d\nreal exp:%d\n",
      expected_error, real_error, expected_mantissa, real_mantissa,
      expected_exp, real_exp);

  printf((real_mantissa == expected_mantissa && real_exp == expected_exp &&
          expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real_error, expected_error);
  ck_assert_int_eq(real_mantissa, expected_mantissa);
  ck_assert_int_eq(real_exp, expected_exp);
  free(dst);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s = suite_create("from_float_to_decimal\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_float_to_decimal_test_nan);
  tcase_add_test(tc_core, s21_from_float_to_decimal_test_too_small);
  tcase_add_test(tc_core, s21_from_float_to_decimal_test_default_small);
  tcase_add_test(tc_core, s21_from_float_to_decimal_test_default_avg);
  tcase_add_test(tc_core, s21_from_float_to_decimal_test_default_big);
  suite_add_tcase(s, tc_core);
  return s;
}