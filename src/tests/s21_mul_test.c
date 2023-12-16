#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"
#include "check.h"

START_TEST(s21_mul_test_overflow) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xFFFAA, 0xACCC, 0x1, 0}};
  s21_decimal second = {{0xAAA, 0x00111, 0x1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int real = s21_mul(first, second, &result);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: ERROR\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_mul_test_test_2) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{122, 0, 0, (15 << 16)}};
  s21_decimal second = {{101, 0, 0, MINUS | (3 << 16)}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mul(first, second, &result);
  s21_decimal expected = {{122 * 101, 0, 0, MINUS | (18 << 16)}};
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: \n");
  s21_decimal_print(&expected);
  printf("\nresult:\n");
  s21_decimal_print(&result);
  int is_success = 1;
  for (int i = 0; i < 4; i++) {
    if (result.bits[i] != expected.bits[i]) {
      is_success = 0;
    }
  }
  printf(is_success ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(is_success, 1);
}
END_TEST

START_TEST(s21_mul_test_test_3) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0x00A00BC, 0XAAA, 0, MINUS | (5 << 16)}};
  s21_decimal second = {{0xBB0FF, 0xFFF, 0, MINUS | (7 << 16)}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mul(first, second, &result);
  s21_decimal expected = {{0xF28BFB44, 0x1CAF3F0E, 0xAA9557, 12 << 16}};
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: \n");
  s21_decimal_print(&expected);
  printf("\nresult:\n");
  s21_decimal_print(&result);
  int is_success = 1;
  for (int i = 0; i < 4; i++) {
    if (result.bits[i] != expected.bits[i]) {
      is_success = 0;
    }
  }
  printf(is_success ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(is_success, 1);
}
END_TEST

START_TEST(s21_mul_test_test_4) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xABBBAC, 0XFAFC, 0, MINUS | (12 << 16)}};
  s21_decimal second = {{0xBCBCAA, 0xF01, 0, 12 << 16}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mul(first, second, &result);
  s21_decimal expected = {
      {0x622CF038, 0x1AB309A0, 0xEB5BFBF, MINUS | (24 << 16)}};
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: \n");
  s21_decimal_print(&expected);
  printf("\nresult:\n");
  s21_decimal_print(&result);
  int is_success = 1;
  for (int i = 0; i < 4; i++) {
    if (result.bits[i] != expected.bits[i]) {
      is_success = 0;
    }
  }
  printf(is_success ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(is_success, 1);
}
END_TEST

START_TEST(s21_mul_test_test_5) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xABA0BB, 0XCC4, 0, MINUS | (9 << 16)}};
  s21_decimal second = {{0xBBA00B, 0xABB, 0, 7 << 16}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_mul(first, second, &result);
  s21_decimal expected = {
      {0xB46DC809, 0x8CCD40CE, 0x88FB3C, MINUS | (16 << 16)}};
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: \n");
  s21_decimal_print(&expected);
  printf("\nresult:\n");
  s21_decimal_print(&result);
  int is_success = 1;
  for (int i = 0; i < 4; i++) {
    if (result.bits[i] != expected.bits[i]) {
      is_success = 0;
    }
  }
  printf(is_success ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(is_success, 1);
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s = suite_create("mul\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_mul_test_overflow);
  tcase_add_test(tc_core, s21_mul_test_test_2);
  tcase_add_test(tc_core, s21_mul_test_test_3);
  tcase_add_test(tc_core, s21_mul_test_test_4);
  tcase_add_test(tc_core, s21_mul_test_test_5);
  suite_add_tcase(s, tc_core);
  return s;
}
