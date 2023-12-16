#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_init_decimal_default(result);
  int sign1 = s21_get_bit(value_1, 128);
  int sign2 = s21_get_bit(value_2, 128);
  int flag = 0;
  int lb = -1;
  if (s21_get_exp(value_1) > s21_get_exp(value_2)) {
    while (s21_get_exp(value_1) > s21_get_exp(value_2) &&
           !s21_get_bit(value_2, 96) && !s21_get_bit(value_2, 95) &&
           !s21_get_bit(value_2, 93) && !s21_get_bit(value_2, 94)) {
      s21_m10(&value_2);
      value_2.bits[3] += 1 << 16;
    }
    while (s21_get_exp(value_1) > s21_get_exp(value_2)) {
      lb = value_2.bits[0] % 2;
      flag += s21_bank_rounding(&value_1, lb,
                                s21_get_exp(value_1) - s21_get_exp(value_2));
    }
  } else if (s21_get_exp(value_1) < s21_get_exp(value_2)) {
    while (s21_get_exp(value_1) < s21_get_exp(value_2) &&
           !s21_get_bit(value_1, 96) && !s21_get_bit(value_1, 95) &&
           !s21_get_bit(value_1, 93) && !s21_get_bit(value_1, 94)) {
      s21_m10(&value_1);
      value_1.bits[3] += 1 << 16;
    }
    while (s21_get_exp(value_1) < s21_get_exp(value_2)) {
      lb = value_1.bits[0] % 2;
      flag += s21_bank_rounding(&value_2, lb,
                                s21_get_exp(value_2) - s21_get_exp(value_1));
    }
  }
  if (sign1 != sign2) {
    s21_negate(value_2, &value_2);
    flag = 2 + s21_add(value_1, value_2, result);
  }
  int ressign = 0;
  if (!flag) {
    long long buf = 0;
    if (s21_is_greater_or_equal(value_1, value_2) && !sign1) {
      buf = (long long)value_1.bits[0] - (long long)value_2.bits[0];
      result->bits[0] = (unsigned int)buf;
      buf =
          (long long)value_1.bits[1] - (long long)value_2.bits[1] + (buf >> 32);
      result->bits[1] = (unsigned int)buf;
      buf =
          (long long)value_1.bits[2] - (long long)value_2.bits[2] + (buf >> 32);
      result->bits[2] = (unsigned int)buf;
      ressign = sign1;
    } else {
      buf = value_2.bits[0] - value_1.bits[0];
      result->bits[0] = (unsigned int)buf;
      buf = value_2.bits[1] - value_1.bits[1] + (buf >> 32);
      result->bits[1] = (unsigned int)buf;
      buf = value_2.bits[2] - value_1.bits[2] + (buf >> 32);
      result->bits[2] = (unsigned int)buf;
      ressign = !sign1;
    }
    //***********************************************************************
    //***********************************************************************
    // Maybe we'll change it
    (ressign) ? s21_set_bit(result, 127, 1) : 0;
    result->bits[3] += s21_get_exp(value_1) << 16;
    // On it???
    // result->bits[3] = s21_get_exp(value_1) << 16;
    // if(ressign)
    //  s21_set_bit(result, 127, 1)
    //***********************************************************************
    //***********************************************************************

    while (s21_get_decimal_digit(*result, 1) == 0 && s21_get_exp(*result) > 0) {
      s21_div_10(result, 1);
      result->bits[3] -= 1 << 16;
    }
  }
  flag = (flag == 2) ? 0 : flag;
  return flag;
}
