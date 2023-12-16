#include "s21_tests.h"

void run_test(Suite *test) {
  SRunner *sr = srunner_create(test);
  printf("\n");
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

int main() {
  run_test(s21_sub_suite());
  run_test(s21_is_not_equal_suite());
  run_test(s21_is_less_suite());
  run_test(s21_is_less_or_equal_suite());
  run_test(s21_is_greater_suite());
  run_test(s21_is_greater_or_equal_suite());
  run_test(s21_is_equal_suite());
  run_test(s21_from_int_to_decimal_suite());
  run_test(s21_from_float_to_decimal_suite());
  run_test(s21_from_decimal_to_int_suite());
  run_test(s21_from_decimal_to_float_suite());
  run_test(s21_add_suite());
  run_test(s21_mul_suite());
  run_test(s21_floor_suite());
  run_test(s21_truncate_suite());
  run_test(s21_round_suite());
  run_test(s21_negate_suite());
  run_test(s21_div_suite());
}