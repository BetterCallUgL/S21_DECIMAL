#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
  int ecode = 0;
  if (((value.bits[3] << 1) >> 17) > 28) {
    ecode = 1;
  } else {
    int bit = value.bits[3] >> 31;
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }

    if (bit) {
      result->bits[3] &= 0x7FFFFFFF;
    } else {
      result->bits[3] |= 0x80000000;
    }
  }

  return ecode;
}