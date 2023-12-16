#include <stdio.h>

#include "s21_utilities.h"

void s21_big_decimal_add(s21_big_decimal* src1, s21_big_decimal* src2) {
  s21_big_decimal result;

  for (int i = 0; i < 7; i++) {
    result.bits[i] = 0;
  }
  result.bits[7] = src1->bits[7];
  int flag = 0;

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 32; j++) {
      int bit1 = (src1->bits[i] >> j) & 1;
      int bit2 = (src2->bits[i] >> j) & 1;
      result.bits[i] |= ((bit1 + bit2 + flag) % 2) << j;
      flag = (bit1 + bit2 + flag > 1) ? 1 : 0;
    }
  }

  for (int i = 0; i < 8; i++) {
    src1->bits[i] = result.bits[i];
  }
}

void s21_multiply_by_ten(s21_big_decimal* src) {
  // сдвиг всего числа, умножение на 2.
  int flag = 0;
  s21_big_decimal tmp;
  for (int j = 0; j < 7; j++) {
    tmp.bits[j] = src->bits[j];
  }
  for (int i = 0; i < 7; i++) {
    src->bits[i] = (src->bits[i] << 1) + flag;
    flag = (tmp.bits[i] >> 31) & 1;
  }

  for (int i = 0; i < 8; i++) {
    tmp.bits[i] = src->bits[i];
  }
  // printf("tmp:\n");
  // s21_big_decimal_print(&tmp);
  for (int i = 0; i < 4; i++) {
    s21_big_decimal_add(src, &tmp);
  }
}