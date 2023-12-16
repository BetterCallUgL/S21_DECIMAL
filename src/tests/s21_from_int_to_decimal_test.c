#include "s21_tests.h"

START_TEST(s21_from_int_to_decimal_test_error) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = NULL;
  int num = 100;
  int real = s21_from_int_to_decimal(num, dst);
  int expected = 1;
  printf(
      "Input: 100, but dst is NULL\nReal error_code: %d\nExpected error_code: "
      "%d\n",
      real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_positive_number) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  int num = 1823772;
  int real_error = s21_from_int_to_decimal(num, dst);
  int expected_error = 0;
  unsigned int real_mantissa = dst->bits[0];
  unsigned int expected_mantissa = 1823772;
  char expected_sign = '+';
  char real_sign = (dst->bits[3] >> 31) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "mantissa:%d\nreal "
      "mantissa:%d\nexpected sign:%c\nreal sign:%c\n",
      expected_error, real_error, expected_mantissa, real_mantissa,
      expected_sign, real_sign);

  printf((real_mantissa == expected_mantissa && real_sign == expected_sign &&
          expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real_mantissa, expected_mantissa);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
  free(dst);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_negative_number) {
  printf("---------------------------------------------\n");
  s21_decimal *dst = (s21_decimal *)malloc(sizeof(s21_decimal));
  int num = -964810;
  int real_error = s21_from_int_to_decimal(num, dst);
  int expected_error = 0;
  unsigned int real_mantissa = dst->bits[0];
  unsigned int expected_mantissa = 964810;
  char expected_sign = '-';
  char real_sign = (dst->bits[3] >> 31) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "mantissa:%d\nreal "
      "mantissa:%d\nexpected sign:%c\nreal sign:%c\n",
      expected_error, real_error, expected_mantissa, real_mantissa,
      expected_sign, real_sign);

  printf((real_mantissa == expected_mantissa && real_sign == expected_sign &&
          expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real_mantissa, expected_mantissa);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
  free(dst);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s = suite_create("from_float_to_decimal\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_error);
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_positive_number);
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_negative_number);
  suite_add_tcase(s, tc_core);
  return s;
}
