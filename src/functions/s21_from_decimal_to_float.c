#include <math.h>
#include <stdio.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  float tt = 0;
  int flag = 0;
  long double exp = 1;
  for (int i = 0; i < (int)s21_get_exp(src); i++) {
    exp /= 10;
  }
  for (int i = 0; i < 28; i++) {
    tt += src.bits[0] % 10 * exp;
    s21_div_10(&src, 1);
    exp *= 10;
    if (tt < 0) {
      flag = 1;
    }
  }
  if (!flag) {
    *dst = (s21_get_bit(src, 128)) ? -tt : tt;
  }
  return flag;
}
