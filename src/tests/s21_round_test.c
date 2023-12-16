#ifndef _UNIT_TEST_ROUND_H_
#define _UNIT_TEST_ROUND_H_

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"
#include "check.h"

START_TEST(s21_round_test_big_positive_number_to_up) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +12345678912345.67891
  // 00010001001000100001000011110100 11000000001000111011011011010011
  // 00010001001000100001000011110100 11000000001000111011011011010011
  num.bits[0] = 0b11000000001000111011011011010011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  // num.bits[2] = 0b1010011101;
  num.bits[3] = 0b101 << 16;
  // 00010001001000100001000011110100 11000000001001000111101000100011
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // +12345678912346
  // 101100111010 01110011110011100101101101011010
  key.bits[0] = 0b01110011110011100101101101011010;
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

START_TEST(s21_round_test_big_positive_number_with_half) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +12345678912344.5
  // 0111000001001000 10000110000011111001000101110101
  // 0111000001001000 10000110000011111001000101110101
  num.bits[0] = 0b10000110000011111001000101110101;
  num.bits[1] = 0b0111000001001000;
  num.bits[3] = 0b1 << 16;
  // 0111000001001000 10000110000011111001000101111010
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // +12345678912345
  // 101100111010 01110011110011100101101101011001
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

START_TEST(s21_round_test_big_positive_number_integer) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +1234567891235
  // 000100011111 01110001111110110000100100100011
  num.bits[0] = 0b01110001111110110000100100100011;
  num.bits[1] = 0b000100011111;
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  char expected_sign = '+';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // +1234567891235
  // 000100011111 01110001111110110000100100100011
  key.bits[0] = 0b01110001111110110000100100100011;
  key.bits[1] = 0b000100011111;

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

START_TEST(s21_round_test_big_positive_number_to_down) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // +12345678912345.17891
  // 00010001001000100001000011110100 11000000001000101111001110000011
  num.bits[0] = 0b11000000001000101111001110000011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  num.bits[3] = 0b101 << 16;

  printf("%u****%u*****%u*****%u\n", num.bits[0], num.bits[1], num.bits[2],
         num.bits[3]);
  int real_error = s21_round(num, &dst);
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

START_TEST(s21_round_test_big_negative_number_to_up) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // -12345678912345.67891
  // 00010001001000100001000011110100 11000000001000111011011011010011
  num.bits[0] = 0b11000000001000111011011011010011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  // num.bits[2] = 0b1010011101;
  num.bits[3] = 0b101 << 16;
  num.bits[3] |= 1u << 31;
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  char expected_sign = '-';
  char real_sign = (s21_get_sign(num)) ? '-' : '+';
  s21_decimal key;
  s21_init_decimal_default(&key);
  // -12345678912346
  // 101100111010 01110011110011100101101101011010
  key.bits[0] = 0b01110011110011100101101101011010;
  key.bits[1] = 0b101100111010;
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

START_TEST(s21_round_test_big_negative_number_with_half) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // -12345678912344.5
  // 0111000001001000 10000110000011111001000101110101
  // 0111000001001000 10000110000011111001000101110101
  num.bits[0] = 0b10000110000011111001000101110101;
  num.bits[1] = 0b0111000001001000;
  num.bits[3] = 0b1 << 16;
  num.bits[3] |= 1u << 31;
  // 0111000001001000 10000110000011111001000101111010
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  s21_decimal key;
  s21_init_decimal_default(&key);
  // -12345678912345
  // 101100111010 01110011110011100101101101011001
  // 101100111010 01110011110011100101101101011001
  key.bits[0] = 0b01110011110011100101101101011001;
  key.bits[1] = 0b101100111010;
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
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_round_test_big_negative_number_integer) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // -1234567891235
  // 000100011111 01110001111110110000100100100011
  num.bits[0] = 0b01110001111110110000100100100011;
  num.bits[1] = 0b000100011111;
  num.bits[3] |= 1u << 31;
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  s21_decimal key;
  s21_init_decimal_default(&key);
  // 1234567891235
  // 000100011111 01110001111110110000100100100011
  key.bits[0] = 0b01110001111110110000100100100011;
  key.bits[1] = 0b000100011111;
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
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_round_test_big_negative_number_to_down) {
  printf("---------------------------------------------\n");
  s21_decimal num, dst;
  s21_init_decimal_default(&num);
  s21_init_decimal_default(&dst);
  // -12345678912345.17891
  // 00010001001000100001000011110100 11000000001000101111001110000011
  num.bits[0] = 0b11000000001000101111001110000011;  // 3 223 566 035
  num.bits[1] = 0b00010001001000100001000011110100;
  num.bits[3] = 0b101 << 16;
  num.bits[3] |= 1u << 31;
  int real_error = s21_round(num, &dst);
  int expected_error = OK;
  s21_decimal key;
  s21_init_decimal_default(&key);
  // -12345678912345
  // 101100111010 01110011110011100101101101011001
  key.bits[0] = 0b01110011110011100101101101011001;
  key.bits[1] = 0b101100111010;
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
  ck_assert_int_eq(real_error, expected_error);
}

START_TEST(s21_round_test_not_expected_mantissa) {
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

  int real_error = s21_round(num, &dst);
  int expected_error = ERROR;
  printf("expected error code:%d\nreal error code:%d\nexpected ",
         expected_error, real_error);
  bool is_ok = expected_error == real_error ? true : false;
  printf(is_ok ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");

  ck_assert_int_eq(real_error, expected_error);
}

Suite *s21_round_suite(void) {
  Suite *s = suite_create("round_func\n");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_round_test_big_positive_number_to_up);
  tcase_add_test(tc_core, s21_round_test_big_positive_number_with_half);
  tcase_add_test(tc_core, s21_round_test_big_positive_number_integer);
  tcase_add_test(tc_core, s21_round_test_big_positive_number_to_down);

  tcase_add_test(tc_core, s21_round_test_big_negative_number_to_up);
  tcase_add_test(tc_core, s21_round_test_big_negative_number_with_half);
  tcase_add_test(tc_core, s21_round_test_big_negative_number_integer);
  tcase_add_test(tc_core, s21_round_test_big_negative_number_to_down);

  tcase_add_test(tc_core, s21_round_test_not_expected_mantissa);

  suite_add_tcase(s, tc_core);
  return s;
}

void run_test_round(Suite *test) {
  SRunner *sr = srunner_create(test);
  printf("\n");
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

#endif  //_UNIT_TEST_ROUND_H_