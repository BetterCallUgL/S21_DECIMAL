#include "s21_utilities.h"

int s21_get_decimal_digit(s21_decimal src, int ind) {
  unsigned long long res = 0;
  if (ind > 0 && ind < 30) {
    s21_div_10(&src, ind - 1);
    for (int i = 1; i < 97; i++) {
      int t = s21_get_bit(src, i) ? 1 : 0;
      if (i != 1) {
        switch (i % 4) {
          case 1:
            t *= 6;
            break;
          case 2:
            t *= 2;
            break;
          case 3:
            t *= 4;
            break;
          case 0:
            t *= 8;
            break;
        }
      }
      res += t;
    }
  } else {
    res = -1;
  }
  // printf("\n");

  res %= 10;
  return res;
}

int s21_get_big_decimal_digit(s21_big_decimal src, int ind) {
  unsigned long long res = 0;
  if (ind > 0 && ind < 30) {
    s21_div_10_big(&src);
    for (int i = 1; i < 7 * 32;
         i++)  // здесь поставь сколько битов считаешь значимыми в биг децимале
    {
      int t = s21_get_bit_big(src, i) ? 1 : 0;
      if (i != 1) {
        switch (i % 4) {
          case 1:
            t *= 6;
            break;
          case 2:
            t *= 2;
            break;
          case 3:
            t *= 4;
            break;
          case 0:
            t *= 8;
            break;
        }
      }
      res += t;
    }
  } else {
    res = -1;
  }
  // printf("\n");

  res %= 10;
  return res;
}
