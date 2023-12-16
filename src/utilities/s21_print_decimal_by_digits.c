#include <stdio.h>

#include "s21_utilities.h"

void s21_print_decimal_by_digits(s21_decimal src) {
  for (int i = 29; i > 0; i--) {
    if ((int)s21_get_exp(src) == i) {
      printf(".");
    }
    printf("%d", s21_get_decimal_digit(src, i));
  }
  if (s21_get_bit(src, 128)) {
    printf("-");
  }
}