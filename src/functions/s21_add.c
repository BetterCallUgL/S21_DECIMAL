#include <math.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init_decimal_default(result);
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
      flag = 2 + s21_sub(value_2, value_1, result);
    } else {
      s21_negate(value_2, &value_2);
      flag = 2 + s21_sub(value_1, value_2, result);
    }
  }
  if (!flag) {
    // Fixed type of buf.
    // It was ul - 32bit, but it must be ll - 64bit
    long long buf =
        (long long)((long long)value_1.bits[0] + (long long)value_2.bits[0]);
    result->bits[0] = (unsigned int)buf;
    buf = (long long)value_1.bits[1] + (long long)value_2.bits[1] + (buf >> 32);
    result->bits[1] = (unsigned int)buf;
    buf = (long long)value_1.bits[2] + (long long)value_2.bits[2] + (buf >> 32);
    if (buf >> 32) {
      flag = 1;
    }
    result->bits[2] = (unsigned int)buf;
    //***********************************************************************
    //***********************************************************************
    // Maybe we'll change it
    sign1 ? s21_set_bit(result, 127, sign1) : sign1;
    result->bits[3] += s21_get_exp(value_1) << 16;
    // On it???
    // result->bits[3] = s21_get_exp(value_1) << 16;
    // if(sign1)
    //  s21_set_bit(result, 127, sign1);
    //***********************************************************************
    //***********************************************************************
  }
  while (s21_get_decimal_digit(*result, 1) == 0 && s21_get_exp(*result) > 0) {
    s21_div_10(result, 1);
    result->bits[3] -= 1 << 16;
  }
  flag = (flag == 2) ? 0 : flag;
  return flag;
}

// int main(){
//     s21_decimal result = {{0,0,0,0}}, res2 = {{0,0,0,0}};
//     s21_decimal d = {{0xF, 0x0, 0x0, 0}};
//     s21_decimal d2 = {{0xFFFF4121, 0x6436, 0xFFFFFA12, 0}};
//     d.bits[3]+= 1<<16;
//     //s21_from_int_to_decimal(123, &d);
//     //s21_from_int_to_decimal(312, &d2);
//     s21_decimal_print(&d);
//     s21_print_decimal_by_digits(d);
//     printf("\n");
//     // s21_negate(d, &d);
//     // s21_decimal_print(&d);
//     // s21_print_decimal_by_digits(d);
//     // printf("\n");
//     s21_decimal_print(&d2);
//     s21_print_decimal_by_digits(d2);
//     printf("\n");
//     s21_add(d, d2, &result);
//     s21_decimal_print(&result);
//     s21_print_decimal_by_digits(result);
//     printf("\n");

//     //s21_decimal_print(&d2);
//     //s21_add(result, d2, &res2);
//     s21_decimal_print(&res2);
//     s21_print_decimal_by_digits(res2);
//     printf("\n");
//     return 0;
// }
