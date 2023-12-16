#ifndef _UNIT_TEST_FLOOR_H_
#define _UNIT_TEST_FLOOR_H_

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"
#include "check.h"

START_TEST(s21_floor_test_big_positive_number) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +12345678912345.67891
  // 00010001001000100001000011110100 11000000001000111011011011010011
  num.bits[0] = 0b11000000001000111011011011010011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  // num.bits[2] = 0b1010011101;
  // num.bits[3] = 0b101 << 16;
  int real_error = s21_floor(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // +12345678912345
  // 101100111010 01110011110011100101101101011001
  key.bits[0] = 0b11000000001000111011011011010011;
  key.bits[1] = 0b00010001001000100001000011110100;
  printf("expected error code:%d\nreal error code:%d\nexpected number:",
         expected_error, real_error);
  printf("%u****%u*****%u*****%u\n", key.bits[0], key.bits[1], key.bits[2],
         key.bits[3]);
  printf("real number:");
  printf("%u****%u*****%u*****%u\n", dst.bits[0], dst.bits[1], dst.bits[2],
         dst.bits[3]);

  bool is_ok = dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
                       dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]
                   ? true
                   : false;

  printf(is_ok && expected_error == real_error ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_floor_test_big_positive_number_to_down) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +12345678912345.67891
  // 00010001001000100001000011110100 11000000001000111011011011010011
  num.bits[0] = 0b11000000001000111011011011010011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  num.bits[3] = 0b101 << 16;
  int real_error = s21_floor(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // +12345678912345
  // 101100111010 01110011110011100101101101011001
  key.bits[0] = 0b01110011110011100101101101011001;
  key.bits[1] = 0b101100111010;
  printf("expected error code:%d\nreal error code:%d\nexpected number:",
         expected_error, real_error);
  printf("%u****%u*****%u*****%u\n", key.bits[0], key.bits[1], key.bits[2],
         key.bits[3]);
  printf("real number:");
  printf("%u****%u*****%u*****%u\n", dst.bits[0], dst.bits[1], dst.bits[2],
         dst.bits[3]);
  bool is_ok = dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
                       dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]
                   ? true
                   : false;

  printf(is_ok && expected_error == real_error ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_floor_test_big_negative_number) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // -123456789132456790
  // 1101101101001101101001011 10101100110100000101111100010110
  num.bits[0] = 0b10101100110100000101111100010110;  // 3 223 566 035
  num.bits[1] = 0b1101101101001101101001011;
  num.bits[3] |= 1u << 31;
  int real_error = s21_floor(num, &dst);
  int expected_error = OK;
  char expected_sign = '-';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // -123456789132456790
  // 1101101101001101101001011 10101100110100000101111100010110
  key.bits[0] = 0b10101100110100000101111100010110;
  key.bits[1] = 0b1101101101001101101001011;
  key.bits[3] |= 1u << 31;
  printf("expected error code:%d\nreal error code:%d\nexpected number:",
         expected_error, real_error);
  printf("%u****%u*****%u*****%u\n", key.bits[0], key.bits[1], key.bits[2],
         key.bits[3]);
  printf("real number:");
  printf("%u****%u*****%u*****%u\n", dst.bits[0], dst.bits[1], dst.bits[2],
         dst.bits[3]);

  bool is_ok = dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
                       dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]
                   ? true
                   : false;

  printf(is_ok && expected_error == real_error ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_floor_test_big_negative_number_to_down) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&dst);
  // -123456789123456789.12345
  // 101001110101000010101101100101100010010001 01110011000101011001101101011001
  num.bits[0] = 0b01110011000101011001101101011001;
  num.bits[1] = 0b01000010101101100101100010010001;
  num.bits[2] = 0b1010011101;
  num.bits[3] = 0b101 << 16;
  s21_set_bit(&num, 127, 1);

  int real_error = s21_floor(num, &dst);
  int expected_error = OK;
  char expected_sign = '-';
  char real_sign = (s21_get_sign(dst)) ? '-' : '+';

  s21_decimal key;
  s21_init_decimal_default(&key);
  // -123456789132456790
  // 1101101101001101101001011 10101100110100000101111100010110
  key.bits[0] = 0b10101100110100000101111100010110;
  key.bits[1] = 0b1101101101001101101001011;
  s21_set_bit(&key, 127, 1);

  printf("expected error code:%d\nreal error code:%d\nexpected number:",
         expected_error, real_error);
  printf("%u****%u*****%u*****%u\n", key.bits[0], key.bits[1], key.bits[2],
         key.bits[3]);
  printf("real number:");
  printf("%u****%u*****%u*****%u\n", dst.bits[0], dst.bits[1], dst.bits[2],
         dst.bits[3]);

  bool is_ok = dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
                       dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]
                   ? true
                   : false;

  printf(is_ok && expected_error == real_error ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert(dst.bits[0] == key.bits[0] && dst.bits[1] == key.bits[1] &&
            dst.bits[2] == key.bits[2] && dst.bits[3] == key.bits[3]);
  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_floor_test_not_expected_mantissa) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&dst);
  // 12345678912345678952345
  // 1010011101 01000010101101100101100010010001
  // 01110011000101100011011110011001
  num.bits[0] = 0b01110011000101100011011110011001;
  num.bits[1] = 0b01000010101101100101100010010001;
  num.bits[2] = 0b1010011101;
  num.bits[3] = 0b11111 << 16;

  int real_error = s21_floor(num, &dst);
  int expected_error = ERROR;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  printf(
      "expected error code:%d\nreal error code:%d\nexpected "
      "expected sign:%c\nreal sign:%c\n",
      expected_error, real_error, expected_sign, real_sign);

  printf((real_sign == expected_sign && expected_error == real_error)
             ? "SUCCESS"
             : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(real_sign, expected_sign);
  ck_assert_int_eq(real_error, expected_error);
}

Suite *s21_floor_suite(void) {
  Suite *s = suite_create("floor_func\n");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_floor_test_big_positive_number);
  tcase_add_test(tc_core, s21_floor_test_big_positive_number_to_down);
  tcase_add_test(tc_core, s21_floor_test_big_negative_number);
  tcase_add_test(tc_core, s21_floor_test_big_negative_number_to_down);
  tcase_add_test(tc_core, s21_floor_test_not_expected_mantissa);

  suite_add_tcase(s, tc_core);
  return s;
}

void run_test_floor(Suite *test) {
  SRunner *sr = srunner_create(test);
  printf("\n");
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

#endif  //_UNIT_TEST_FLOOR_H_