#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_div_10(&src, s21_get_exp(src));
  *dst = (s21_get_bit(src, 128)) ? -src.bits[0] : src.bits[0];
  return (src.bits[1] || src.bits[2] || s21_get_bit(src, 32)) ? 1 : 0;
}