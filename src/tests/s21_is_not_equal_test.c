#include "s21_tests.h"

START_TEST(s21_is_not_equal_test_1_positive_negative_number) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_2_negative_positive_number) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{1, 0, 0, MINUS}};
  s21_decimal second = {{1, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_3_positive_number1) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0, 0, 0}};
  s21_decimal second = {{1, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_4_positive_number0) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0, 0, 0}};
  s21_decimal first = {{1, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_5_negative_number0) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0, 0, MINUS}};
  s21_decimal second = {{1, 0, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_6_negative_number1) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0, 0, MINUS}};
  s21_decimal first = {{1, 0, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_8_positive_number1_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0xAAA, 0, 0}};
  s21_decimal second = {{0xAAA, 0xAAA, 0, (12 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_7_positive_number0_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0xAAA, 0, 0}};
  s21_decimal first = {{0xAAA, 0xAAA, 0, (12 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_9_negative_number0_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0xAAA, 0, MINUS}};
  s21_decimal second = {{0xAAA, 0xAAA, 0, MINUS | (9 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_10_negative_number1_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0xABA, 0, MINUS}};
  s21_decimal first = {{0xAAA, 0xABA, 0, MINUS | (9 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_12_positive_number1_raznie_stepeni_big) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0, 0, 0}};
  s21_decimal second = {{0, 0, 0x1, (12 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_11_positive_number0_raznie_stepeni_big) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0, 0, 0}};
  s21_decimal first = {{0xAAA, 0, 0x1, (12 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_13_negative_number0_raznie_stepeni_big) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xAAA, 0xAAA, 0, MINUS}};
  s21_decimal second = {{0xAAA, 0xAAA, 0x1, MINUS | (9 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_14_negative_number1_raznie_stepeni_big) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0xABA, 0, MINUS}};
  s21_decimal first = {{0xAAA, 0xABA, 0x1, MINUS | (9 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 1;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 1\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_15_negative) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0xAAA, 0, MINUS}};
  s21_decimal first = {{0xAAA, 0xAAA, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_16_positive) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0xAAA, 0xAAA, 0, 0}};
  s21_decimal first = {{0xAAA, 0xAAA, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_17_min0) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0, 0, 0, 0}};
  s21_decimal first = {{0, 0, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_18_min0) {
  printf("---------------------------------------------\n");
  s21_decimal second = {{0, 0, 0, MINUS}};
  s21_decimal first = {{0, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_19_eq_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{1, 0, 0, 0}};
  s21_decimal second = {{0xA, 0, 0, 0 | (1 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_20_eq_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0xA, 0, 0, 0 | (1 << 16)}};
  s21_decimal second = {{1, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_21_minus_eq_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0x52F482, 0, 0, MINUS}};
  s21_decimal second = {{0x206782C8, 0, 0, MINUS | (2 << 16)}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_22_minus_eq_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0x206782C8, 0, 0, MINUS | (2 << 16)}};
  s21_decimal second = {{0x52F482, 0, 0, MINUS}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

START_TEST(s21_is_not_equal_test_23_eq0_raznie_stepeni) {
  printf("---------------------------------------------\n");
  s21_decimal first = {{0, 0, 0, 0 | (2 << 16)}};
  s21_decimal second = {{0, 0, 0, 0}};
  int real = s21_is_not_equal(first, second);
  int expected = 0;
  printf("first num:\n");
  s21_decimal_print(&first);
  printf("\nsecond num:\n");
  s21_decimal_print(&second);
  printf("\nexpected: 0\n");
  printf(real == expected ? "SUCCESS" : "FAIL");
  printf("\n---------------------------------------------\n");
  ck_assert_int_eq(real, expected);
}
END_TEST

Suite *s21_is_not_equal_suite(void) {
  Suite *s = suite_create("is_not_equal\n");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_is_not_equal_test_1_positive_negative_number);
  tcase_add_test(tc_core, s21_is_not_equal_test_2_negative_positive_number);
  tcase_add_test(tc_core, s21_is_not_equal_test_3_positive_number1);
  tcase_add_test(tc_core, s21_is_not_equal_test_4_positive_number0);
  tcase_add_test(tc_core, s21_is_not_equal_test_5_negative_number0);
  tcase_add_test(tc_core, s21_is_not_equal_test_6_negative_number1);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_7_positive_number0_raznie_stepeni);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_8_positive_number1_raznie_stepeni);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_9_negative_number0_raznie_stepeni);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_10_negative_number1_raznie_stepeni);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_11_positive_number0_raznie_stepeni_big);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_12_positive_number1_raznie_stepeni_big);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_13_negative_number0_raznie_stepeni_big);
  tcase_add_test(tc_core,
                 s21_is_not_equal_test_14_negative_number1_raznie_stepeni_big);
  tcase_add_test(tc_core, s21_is_not_equal_test_15_negative);
  tcase_add_test(tc_core, s21_is_not_equal_test_16_positive);
  tcase_add_test(tc_core, s21_is_not_equal_test_17_min0);
  tcase_add_test(tc_core, s21_is_not_equal_test_18_min0);
  tcase_add_test(tc_core, s21_is_not_equal_test_19_eq_raznie_stepeni);
  tcase_add_test(tc_core, s21_is_not_equal_test_20_eq_raznie_stepeni);
  tcase_add_test(tc_core, s21_is_not_equal_test_21_minus_eq_raznie_stepeni);
  tcase_add_test(tc_core, s21_is_not_equal_test_22_minus_eq_raznie_stepeni);
  tcase_add_test(tc_core, s21_is_not_equal_test_23_eq0_raznie_stepeni);
  suite_add_tcase(s, tc_core);
  return s;
}