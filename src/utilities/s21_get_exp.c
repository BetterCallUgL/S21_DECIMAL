#include "s21_utilities.h"

size_t s21_get_exp(s21_decimal d) {
  d.bits[3] &= ~(1 << 31);
  d.bits[3] >>= 16;
  return d.bits[3];
}