#include "s21_utilities.h"

void s21_set_bit(s21_decimal *src, int num, int bit) {
  if (num >= 0 && num < 128 && (bit == 0 || bit == 1)) {
    if (bit == 1) {
      src->bits[num / 32] |= 1 << (num % 32);
    } else {
      src->bits[num / 32] -= 1 << (num % 32);
    }
  }
}