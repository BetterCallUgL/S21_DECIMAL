#include "s21_tests.h"

START_TEST(s21_sub_test_default) {
  printf("---------------------------------------------\n");
  s21_decimal d1 = {{123, 0, 0, 0}};
  s21_decimal d2 = {{321, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  int expected = d1.bits[0] - d2.bits[0];
  int real = result.bits[0] * (-1 * s21_get_bit(result, 128));
  printf("Input: 123-321\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_sub_test_minus) {
  s21_decimal d1 = {{123, 0, 0, MINUS}};
  s21_decimal d2 = {{321, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  int expected = -321 - 123;
  int real = result.bits[0] * (-1 * s21_get_bit(result, 128));
  printf("Input: -123-321\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_sub_test_minus_res) {
  s21_decimal d1 = {{123, 0, 0, 0}};
  s21_decimal d2 = {{321, 0, 0, MINUS}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  int expected = 123 - -321;
  int real;
  s21_from_decimal_to_int(result, &real);
  // s21_decimal_print(&result);
  printf("Input: 123 - -321\nReal output: %d\nExpected: %d\n", real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_sub_test_small_float) {
  s21_decimal d1 = {{123, 0, 0, 0}};
  s21_decimal d2 = {{4321, 0, 0, 0}};
  d1.bits[3] += 3 << 16;
  d2.bits[3] += 3 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  float expected = 0.123 - 4.321;
  float real;
  s21_from_decimal_to_float(result, &real);
  printf("Input: 0.123-4.321\nReal output: %f\nExpected: %f\n", real, expected);
  printf(real - expected < 1e-6 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-6);
}
END_TEST

START_TEST(s21_sub_test_dif_exp) {
  s21_decimal d1 = {{123, 0, 0, 0}};
  s21_decimal d2 = {{4321, 0, 0, 0}};
  d1.bits[3] += 3 << 16;
  d2.bits[3] += 4 << 16;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  float expected = 0.123 - 0.4321;
  float real;
  // s21_decimal_print(&d1);
  // s21_decimal_print(&d2);
  // s21_decimal_print(&result);
  s21_from_decimal_to_float(result, &real);
  printf("Input: 0.123-0.4321\nReal output: %f\nExpected: %f\n", real,
         expected);
  printf(real - expected < 1e-6 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_float_eq_tol(real, expected, 1e-6);
}
END_TEST

START_TEST(s21_sub_test_bignums) {
  s21_decimal d1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0x4321, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(d1, d2, &result);
  unsigned long int expected =
      (unsigned long int)0xFFFFFFFFFFFFFFFE - (unsigned long int)0x4321FFFFFFFF;
  unsigned long int real =
      (unsigned long int)((unsigned long int)result.bits[0] +
                          ((unsigned long int)result.bits[1] << 32));
  s21_decimal_print(&result);
  printf(
      "Input: 0xFFFFFFFFFFFFFFFFFFFFFFFF - 0xFFFFFFFFF00004321FFFFFFFD\nReal "
      "output: %lu\nExpected: %lu\n",
      real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_sub_test_overfill_err) {
  s21_decimal d1 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, MINUS}};
  s21_decimal result = {{0, 0, 0, 0}};
  int expected = 3;
  int real = s21_sub(d1, d2, &result);
  // s21_decimal_print(&result);
  // long int real = result.bits[0] + ((long int)result.bits[1]<<32);
  printf(
      "Input: 0xFFFFFFFF00000000FFFFFFFF - -0xFFFFFFFF00000000FFFFFFFF\nReal "
      "output: error %d\nExpected: error %d\n",
      real, expected);
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_sub_test_bank_roundingp1) {
  s21_decimal d1 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{151234, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  d2.bits[3] += 5 << 16;
  unsigned int ex1 = 0xFFFFFFFE;
  unsigned int ex2 = 0x0;
  unsigned int ex3 = 0xFFFFFFFF;
  s21_sub(d1, d2, &result);
  printf(
      "Input: 0xFFFFFFFF00000000FFFFFFFF - 1.51234\nReal output: "
      "%8x%8x%8x\nExpected: %8x%8x%8x\n",
      result.bits[0], result.bits[1], result.bits[2], ex1, ex2, ex3);
  printf(1 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(ex1, result.bits[0]);
  ck_assert_int_eq(ex2, result.bits[1]);
  ck_assert_int_eq(ex3, result.bits[2]);
}
END_TEST

START_TEST(s21_sub_test_bank_roundingp2) {
  s21_decimal d1 = {{0xFFFFFFFE, 0, 0xFFFFFFFF, 0}};
  s21_decimal d2 = {{151234, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  d2.bits[3] += 5 << 16;
  unsigned int ex1 = 0xFFFFFFFC;
  unsigned int ex2 = 0x0;
  unsigned int ex3 = 0xFFFFFFFF;
  s21_sub(d1, d2, &result);
  printf(
      "Input: 0xFFFFFFFF00000000FFFFFFFE - 1.51234\nReal output: "
      "%8x%8x%8x\nExpected: %8x%8x%8x\n",
      result.bits[0], result.bits[1], result.bits[2], ex1, ex2, ex3);
  printf(1 ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(ex1, result.bits[0]);
  ck_assert_int_eq(ex2, result.bits[1]);
  ck_assert_int_eq(ex3, result.bits[2]);
}
END_TEST

Suite *s21_sub_suite(void) {
  Suite *s = suite_create("sub\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_sub_test_default);
  tcase_add_test(tc_core, s21_sub_test_minus);
  tcase_add_test(tc_core, s21_sub_test_minus_res);
  tcase_add_test(tc_core, s21_sub_test_small_float);
  tcase_add_test(tc_core, s21_sub_test_bignums);
  tcase_add_test(tc_core, s21_sub_test_dif_exp);
  tcase_add_test(tc_core, s21_sub_test_overfill_err);
  tcase_add_test(tc_core, s21_sub_test_bank_roundingp1);
  tcase_add_test(tc_core, s21_sub_test_bank_roundingp2);
  suite_add_tcase(s, tc_core);
  return s;
}
