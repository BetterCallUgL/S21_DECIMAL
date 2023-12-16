#include "s21_utilities.h"

void s21_big_decimal_init(s21_decimal* src, s21_big_decimal* dst) {
  for (int i = 0; i < 7; i++) {
    if (i < 3) {
      dst->bits[i] = src->bits[i];
    } else {
      dst->bits[i] = 0;
    }
  }
  dst->bits[7] = src->bits[3];
}

void s21_decimal_init(s21_decimal* src, s21_decimal* dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src->bits[i];
  }
}