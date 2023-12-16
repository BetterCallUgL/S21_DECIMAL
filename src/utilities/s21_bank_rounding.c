#include "s21_utilities.h"

int s21_bank_rounding(s21_decimal *src, int lb, int exp) {
  int flag = 0;
  s21_div_10(src, exp - 1);
  int a = s21_get_decimal_digit(*src, 1);
  s21_div_10(src, 1);
  src->bits[3] -= exp << 16;
  s21_decimal ONE = {{1, 0, 0, src->bits[3]}};
  if (a == 5) {
    if ((src->bits[0] % 2 == 1 && !lb) || (src->bits[0] % 2 == 0 && lb)) {
      flag = s21_add(*src, ONE, src);
    }
  } else if (a > 5) {
    flag = s21_add(*src, ONE, src);
  }
  return flag;
}

void add_one_to_big(s21_big_decimal *src);

int s21_bank_rounding_big(
    s21_big_decimal *src) {  // для корректной работы проверь функции в
                             // s21_get_decimal_digit.c и s21_div_10
  int flag = 0;
  int last;
  while (((src->bits[6] || src->bits[5] || src->bits[4] || src->bits[3] ||
           (abs((int)src->bits[7] >> 16)) > 28)) &&
         (int)src->bits[7] != 0) {
    last = s21_get_big_decimal_digit(*src, 1);
    s21_div_10_big(src);
    src->bits[7] -= 1 << 16;
  }
  if (last > 5) {
    add_one_to_big(src);
  } else if (last == 5) {
    if (src->bits[0] % 2 == 1) {
      add_one_to_big(src);
    }
  }
  if ((src->bits[6] || src->bits[5] || src->bits[4] || src->bits[3] ||
       (abs((int)src->bits[7] >> 16)) > 28)) {
    flag = 1;
  }
  return flag;
}

int s21_bank_rounding_div(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result) {
  int flag = 0;
  s21_decimal ONE = {{1, 0, 0, result->bits[3]}};
  s21_decimal tt;
  s21_mul(value_1, (s21_decimal){{2, 0, 0, 0}}, &tt);
  if (s21_is_equal(tt, value_2)) {
    if (result->bits[0] % 2 == 1) {
      flag = s21_add(*result, ONE, result);
    }
  } else if (s21_is_greater(tt, value_2)) {
    flag = s21_add(*result, ONE, result);
  }
  return flag;
}

void add_one_to_big(s21_big_decimal *src) {
  long unsigned int buf = 0;
  for (int i = 0; i < 7; i++) {
    buf = (long unsigned int)((long unsigned int)src->bits[1] +
                              (long unsigned int)1) +
          (buf >> 32);
    src->bits[i] = (unsigned int)buf;
  }
}