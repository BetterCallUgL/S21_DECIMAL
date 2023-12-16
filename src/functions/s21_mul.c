#include <limits.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"
#include "stdio.h"

void s21_big_decimal_copy(s21_big_decimal* src, s21_big_decimal* dst) {
  for (int i = 0; i < 8; i++) {
    dst->bits[i] = src->bits[i];
  }
}

int s21_is_zero(s21_big_decimal* src) {
  int result = 1;
  for (int i = 0; i < 7; i++) {
    if (src->bits[i] != 0) {
      result = 0;
    }
  }

  return result;
}

void s21_left_shift(s21_big_decimal* src) {
  int flag = 0;
  s21_big_decimal tmp;
  for (int j = 0; j < 7; j++) {
    tmp.bits[j] = src->bits[j];
  }
  for (int i = 0; i < 7; i++) {
    src->bits[i] = (src->bits[i] << 1) + flag;
    flag = (tmp.bits[i] >> 31) & 1;
  }
}

void s21_right_shift(s21_big_decimal* src) {
  for (int i = 0; i < 7; i++) {
    src->bits[i] = src->bits[i] >> 1;
    if (i < 6) {
      src->bits[i] |= (src->bits[i + 1] & 1) << 31;
    }
  }
}

int big_bits_not_zero(s21_big_decimal src) {
  int result = 0;
  for (int i = 3; i < 7; i++) {
    if (src.bits[i]) {
      result = 1;
    }
  }

  return result;
}

// 1 - влезает в decimal, но exp > 28
// 2 - не влезает в decimal
void s21_bank_rounding_for_mul(s21_big_decimal* result) {
  int r = 0;
  // обнулил знак
  int sign = (result->bits[7]) >> 31;
  int exp = ((result->bits[7] << 1) >> 17);
  result->bits[7] = 0;

  while (exp > 28) {
    r = s21_div_10_big(result);
    --exp;
  }

  // 2
  if (big_bits_not_zero(*result)) {
    while (exp > 0 && big_bits_not_zero(*result)) {
      r = s21_div_10_big(result);
      --exp;
    }
  }

  if (r > 5 || (r == 5 && result->bits[0] % 2 == 1)) {
    s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0, 0}};
    s21_big_decimal_add(result, &one);
  }

  if (sign) {
    result->bits[7] |= MINUS;
  }
  result->bits[7] |= exp << 16;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int returning_value = 0;
  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  s21_big_decimal_init(&value_1, &big_value_1);
  s21_big_decimal_init(&value_2, &big_value_2);

  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }

  s21_big_decimal big_result = {{0, 0, 0, 0, 0, 0, 0, 0}};

  result->bits[3] |=
      ((((value_1.bits[3] << 1) >> 17) + ((value_2.bits[3] << 1) >> 17)) << 16);
  unsigned int value1_is_minus = value_1.bits[3] >> 31;
  unsigned int value2_is_minus = value_2.bits[3] >> 31;
  if ((value1_is_minus && !value2_is_minus) ||
      (value2_is_minus && !value1_is_minus)) {
    result->bits[3] |= MINUS;
  }
  big_result.bits[7] = result->bits[3];

  while (!s21_is_zero(&big_value_2)) {
    if ((big_value_2.bits[0] & 1) == 1) {
      s21_big_decimal_add(&big_result, &big_value_1);
    }

    s21_left_shift(&big_value_1);
    s21_right_shift(&big_value_2);
  }

  /*
    while (((big_result.bits[7] << 1) >> 17) > 0 &&
           big_bits_not_zero(big_result)) {
      s21_bank_rounding_big(&big_result);
    }
  */

  s21_bank_rounding_for_mul(&big_result);
  if (big_bits_not_zero(big_result) && (big_result.bits[7] >> 31) == 0) {
    returning_value = 1;
  } else if (big_bits_not_zero(big_result) && (big_result.bits[7] >> 31) == 1) {
    returning_value = 2;
  } else {
    for (int i = 0; i < 3; i++) {
      result->bits[i] = big_result.bits[i];
    }
    result->bits[3] = big_result.bits[7];
  }

  return returning_value;
}

// int main() {
//   s21_decimal a = {0xff, 0xff, 0, MINUS | (15 << 15)};
//   s21_decimal b = {0xff, 0xff, 0, 0};
//   printf("first:\n");
//   s21_decimal_print(&a);
//   printf("\nsecond:\n");
//   s21_decimal_print(&b);
//   s21_decimal* result = malloc(sizeof(s21_decimal));
//   if (s21_mul(a, b, result)) {
//     printf("ERROR!");
//   }
//   printf("\nresult:\n");
//   s21_decimal_print(result);
// }
