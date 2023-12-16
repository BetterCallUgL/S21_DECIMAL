#include "s21_utilities.h"

void s21_init_decimal_default(s21_decimal* d) {
  d->bits[0] = d->bits[1] = d->bits[2] = d->bits[3] = 0;
}

int s21_init_decimal_copy(s21_decimal* to, s21_decimal from) {
  if (!to) return ERROR;
  if (to != &from)
    for (int i = 0; i < 4; ++i) to->bits[i] = from.bits[i];
  return OK;
}

bool s21_my_get_bit(s21_decimal d, size_t n) {
  return d.bits[n / 32] & (1u << n % 32);
}

int s21_get_sign(s21_decimal d) { return d.bits[3] & (1u << 31); }

int s21_my_set_bit(s21_decimal* d, size_t n, int value) {
  return value ? (d->bits[n / 32] |= (1u << n % 32))
               : (d->bits[n / 32] &= (~(1u << n % 32)));
}

int s21_add_for_truncate(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal* result) {
  int sign1 = s21_get_bit(value_1, 128);
  int sign2 = s21_get_bit(value_2, 128);
  int flag = 0;
  int lb = 0;
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
    if (sign1) {
      s21_negate(value_1, &value_1);
      flag = 2 + s21_sub_for_truncate(value_2, value_1, result);
    } else {
      s21_negate(value_2, &value_2);
      flag = 2 + s21_sub_for_truncate(value_1, value_2, result);
    }
  }
  if (!flag) {
    // Fixed type of buf.
    // It was ul - 32bit, but it must be ll - 64bit
    long long buf = (long long)value_1.bits[0] + (long long)value_2.bits[0];
    result->bits[0] = (unsigned int)buf;
    buf = (long long)value_1.bits[1] + (long long)value_2.bits[1] + (buf >> 32);
    result->bits[1] = (unsigned int)buf;
    buf = (long long)value_1.bits[2] + (long long)value_2.bits[2] + (buf >> 32);
    if (buf >> 31) {
      flag = 1;
    }
    result->bits[2] = (unsigned int)buf;
    //***********************************************************************
    //***********************************************************************
    // Maybe we'll change it
    // sign1 ? s21_set_bit(result, 127, sign1) : sign1;
    // result->bits[3] += s21_get_exp(value_1) << 16;
    // On it???
    result->bits[3] = s21_get_exp(value_1) << 16;
    if (sign1) s21_set_bit(result, 127, sign1);
    //***********************************************************************
    //***********************************************************************
  }
  /*
  while (s21_get_decimal_digit(*result, 1) == 0 && s21_get_exp(*result) > 0) {
    s21_div_10(result, 1);
    result->bits[3] -= 1 << 16;
  }*/
  flag = (flag == 2) ? 0 : flag;
  return flag;
}

int s21_sub_for_truncate(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal* result) {
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
    flag = 2 + s21_add_for_truncate(value_1, value_2, result);
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
    // (ressign) ? s21_set_bit(result, 127, 1) : 0;
    // result->bits[3] += s21_get_exp(value_1) << 16;
    // On it???
    result->bits[3] = s21_get_exp(value_1) << 16;
    if (ressign) s21_set_bit(result, 127, 1);
    //***********************************************************************
    //***********************************************************************
    /*
    while (s21_get_decimal_digit(*result, 1) == 0 && s21_get_exp(*result) > 0) {
      s21_div_10(result, 1);
      result->bits[3] -= 1 << 16;
    }*/
  }
  flag = (flag == 2) ? 0 : flag;
  return flag;
}

int s21_shift_decimal_left(s21_decimal* result, size_t shift) {
  int ret = OK;
  if (shift > 96)
    ret = ERROR;
  else {
    if (shift) {
      int j = 95;
      int int_shift = shift;
      while (j >= int_shift)
        s21_my_set_bit(result, j, s21_my_get_bit(*result, j - int_shift)), --j;
      while (j >= 0) s21_my_set_bit(result, j, 0), --j;
    }
    ret = OK;
  }
  return ret;
}

int s21_my_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) return ERROR;
  s21_init_decimal_default(result);
  s21_decimal residue, tmp;
  s21_init_decimal_default(&residue);
  s21_init_decimal_default(&tmp);
  if (s21_get_sign(value_1) ^ s21_get_sign(value_2))
    result->bits[3] |= 1u << 31;
  for (int i = 95; i >= 0; --i) {
    s21_shift_decimal_left(&residue, 1u);
    s21_my_set_bit(&residue, 0, s21_my_get_bit(value_1, i));
    if (s21_is_greater(residue, value_2) || s21_is_equal(residue, value_2)) {
      s21_sub(residue, value_2, &tmp);
      s21_init_decimal_copy(&residue, tmp);
      s21_init_decimal_default(&tmp);
      s21_my_set_bit(result, i, 1);
    }
  }
  return 0;
}