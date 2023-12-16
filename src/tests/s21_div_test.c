#include "s21_tests.h"

START_TEST(s21_div_test_default) {
  printf("---------------------------------------------\n");
  s21_decimal d1 = {{100, 0, 0, 0}};
  s21_decimal d2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(d1, d2, &result);
  int expected = 10;
  int real = result.bits[0];
  printf("Input: 100 / 10 \nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_div_test_minus) {
  s21_decimal d1 = {{100, 0, 0, MINUS}};
  s21_decimal d2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(d1, d2, &result);
  int expected = -10;
  int real = result.bits[0] * (-1 * s21_get_bit(result, 128));
  printf("Input: -100 / 10\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_div_test_minus_res) {
  s21_decimal d1 = {{100, 0, 0, 0}};
  s21_decimal d2 = {{10, 0, 0, MINUS}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(d1, d2, &result);
  int expected = -10;
  int real = result.bits[0] * (-1 * s21_get_bit(result, 128));
  // s21_decimal_print(&result);
  printf("Input: 100/-10\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_div_test_small_float) {
  s21_decimal d1 = {{5, 0, 0, 0}};
  s21_decimal d2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(d1, d2, &result);
  float expected = 2.5;
  float real;
  s21_from_decimal_to_float(result, &real);
  printf("Input: 5/2\nReal output: %f\nExpected: %f\n", real, expected);
  printf(real - expected < 1e-6 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-6);
}
END_TEST

START_TEST(s21_div_test_dif_exp) {
  s21_decimal d1 = {{1, 0, 0, 0}};
  s21_decimal d2 = {{1, 0, 0, 0}};
  d1.bits[3] += 3 << 16;
  d2.bits[3] += 4 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_div(d1, d2, &result);
  float expected = 10;
  float real;
  // s21_decimal_print(&d1);
  // s21_decimal_print(&d2);
  // s21_decimal_print(&result);
  s21_from_decimal_to_float(result, &real);
  printf("Input: 0.001/0.0001\nReal output: %f\nExpected: %f\n", real,
         expected);
  printf(real - expected < 1e-6 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-6);
}
END_TEST

START_TEST(s21_div_test_bignums) {
  s21_decimal d1 = {{0x1, 0, 0, 0}};
  s21_decimal d2 = {{0x3, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  unsigned int ex1 = 0x05555555;
  unsigned int ex2 = 0x14B700CB;
  unsigned int ex3 = 0xAC544CA;
  s21_div(d1, d2, &result);
  printf(
      "Input: 10/3 \nReal output: "
      "%8x %8x %8x\nExpected: %8x %8x %8x\n",
      result.bits[0], result.bits[1], result.bits[2], ex1, ex2, ex3);
  printf(1 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(ex1, result.bits[0]);
  ck_assert_int_eq(ex2, result.bits[1]);
  ck_assert_int_eq(ex3, result.bits[2]);
}
END_TEST

START_TEST(s21_div_test_overfill_err) {
  s21_decimal d1 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int expected = 3;
  int real = s21_div(d1, d2, &result);
  // s21_decimal_print(&result);
  // long int real = result.bits[0] + ((long int)result.bits[1]<<32);
  printf(
      "Input: 0xFFFFFFFF00000000FFFFFFFF / 0\nReal "
      "output: error %d\nExpected: error %d\n",
      real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_div_test_bank_roundingp1) {
  s21_decimal d1 = {{20, 0, 0, 0}};
  s21_decimal d2 = {{3, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  unsigned int ex1 = 0x6AAAAAAB;
  unsigned int ex2 = 0x9e4c0fdc;
  unsigned int ex3 = 0xd7695fc9;
  s21_div(d1, d2, &result);
  printf(
      "Input: 20/3 \nReal output: "
      "%8x%8x%8x\nExpected: %8x%8x%8x\n",
      result.bits[0], result.bits[1], result.bits[2], ex1, ex2, ex3);
  printf(1 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(ex1, result.bits[0]);
  ck_assert_int_eq(ex2, result.bits[1]);
  ck_assert_int_eq(ex3, result.bits[2]);
}
END_TEST

START_TEST(s21_div_test_overfill_err_big) {
  s21_decimal d1 = {{0xFFFFFFFF, 0, 0xFFFFFFF, 0}};
  s21_decimal d2 = {{1, 0, 0, 28 << 16}};
  s21_decimal result = {{0, 0, 0, 0}};
  int expected = 1;
  int real = s21_div(d1, d2, &result);
  // s21_decimal_print(&result);
  // long int real = result.bits[0] + ((long int)result.bits[1]<<32);
  printf(
      "Input: 0xFFFFFFFF00000000FFFFFFFF / 1e-28\nReal "
      "output: error %d\nExpected: error %d\n",
      real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s = suite_create("div\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_div_test_default);
  tcase_add_test(tc_core, s21_div_test_minus);
  tcase_add_test(tc_core, s21_div_test_minus_res);
  tcase_add_test(tc_core, s21_div_test_small_float);
  tcase_add_test(tc_core, s21_div_test_bignums);
  tcase_add_test(tc_core, s21_div_test_dif_exp);
  tcase_add_test(tc_core, s21_div_test_overfill_err);
  tcase_add_test(tc_core, s21_div_test_bank_roundingp1);
  tcase_add_test(tc_core, s21_div_test_overfill_err_big);
  suite_add_tcase(s, tc_core);
  return s;
}