#ifndef _UNIT_TEST_NEGATE_H_
#define _UNIT_TEST_NEGATE_H_

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"
#include "check.h"

START_TEST(s21_negate_test_big_positive_number) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&dst);
  // +123456789123456789.12345
  num.bits[0] = 0b01110011000101011001101101011001;
  num.bits[1] = 0b01000010101101100101100010010001;
  num.bits[2] = 0b1010011101;
  num.bits[3] = 0b101 << 16;
  int real_error = s21_negate(num, &dst);
  int expected_error = OK;
  char expected_sign = '-';
  char real_sign = (s21_get_sign(dst)) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      //"mantissa:%d\nreal "
      //"mantissa:%d\n"
      "expected sign:%c\nreal sign:%c\n",
      expected_error, real_error,  // expected_mantissa, real_mantissa,
      expected_sign, real_sign);

  printf((  // real_mantissa == expected_mantissa &&
             real_sign == expected_sign && expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  s21_decimal key;
  s21_init_decimal_default(&key);
  key.bits[0] = 0b01110011000101011001101101011001;
  key.bits[1] = 0b01000010101101100101100010010001;
  key.bits[2] = 0b1010011101;
  key.bits[3] = 0b101 << 16;
  s21_my_set_bit(&key, 127, 1);
  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_negate_test_big_negative_number) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&dst);
  // 123456789123456789.52345
  // 1010011101 01000010101101100101100010010001
  // 01110011000101100011011110011001
  num.bits[0] = 0b01110011000101100011011110011001;
  num.bits[1] = 0b01000010101101100101100010010001;
  num.bits[2] = 0b1010011101;
  num.bits[3] = 0b101 << 16;
  s21_my_set_bit(&num, 127, 1);

  int real_error = s21_negate(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(dst)) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      // "mantissa:%d\nreal "
      // "mantissa:%d\n"
      "expected sign:%c\nreal sign:%c\n",
      expected_error, real_error,  // expected_mantissa, real_mantissa,
      expected_sign, real_sign);

  printf((  // real_mantissa == expected_mantissa &&
             real_sign == expected_sign && expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");
  s21_decimal key;
  s21_init_decimal_default(&key);
  key.bits[0] = 0b01110011000101100011011110011001;
  key.bits[1] = 0b01000010101101100101100010010001;
  key.bits[2] = 0b1010011101;
  key.bits[3] = 0b101 << 16;
  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_negate_test_not_expected_mantissa) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&dst);
  // 123456789123456789.52345
  // 1010011101 01000010101101100101100010010001
  // 01110011000101100011011110011001
  num.bits[0] = 0b01110011000101100011011110011001;
  num.bits[1] = 0b01000010101101100101100010010001;
  num.bits[2] = 0b1010011101;
  num.bits[3] = 0b11111 << 16;

  int real_error = s21_negate(num, &dst);
  int expected_error = ERROR;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      //"mantissa:%d\nreal "
      //"mantissa:%d\n"
      "expected sign:%c\nreal sign:%c\n",
      expected_error, real_error,  // expected_mantissa, real_mantissa,
      expected_sign, real_sign);

  printf((  // real_mantissa == expected_mantissa &&
             real_sign == expected_sign && expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

Suite *s21_negate_suite(void) {
  Suite *s = suite_create("negate_func\n");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_negate_test_big_positive_number);
  tcase_add_test(tc_core, s21_negate_test_big_negative_number);
  tcase_add_test(tc_core, s21_negate_test_not_expected_mantissa);

  suite_add_tcase(s, tc_core);
  return s;
}

void run_test_negate(Suite *test) {
  SRunner *sr = srunner_create(test);
  printf("\n");
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

#endif  //_UNIT_TEST_NEGATE_H_