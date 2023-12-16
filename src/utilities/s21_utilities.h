#ifndef S21_BIG_DECIMAL
#define S21_BIG_DECIMAL
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

void s21_decimal_init(s21_decimal *src, s21_decimal *dst);
void s21_big_decimal_init(s21_decimal *src, s21_big_decimal *dst);
void s21_multiply_by_ten(s21_big_decimal *src);
void s21_decimal_print(s21_decimal *dst);
void s21_big_decimal_print(s21_big_decimal *dst);
int s21_get_bit(s21_decimal d, size_t n);
size_t s21_get_exp(s21_decimal d);
void s21_big_decimal_add(s21_big_decimal *src1, s21_big_decimal *src2);
int s21_get_bit_big(s21_big_decimal d, size_t n);
int s21_div_10(s21_decimal *result, int move);
int s21_get_decimal_digit(s21_decimal src, int ind);
void s21_print_decimal_by_digits(s21_decimal src);
int s21_bank_rounding(s21_decimal *src, int lb, int exp);
int s21_bank_rounding_div(s21_decimal value_1, s21_decimal value_2,
                          s21_decimal *result);
int s21_bank_rounding_big(s21_big_decimal *src);
void s21_set_bit(s21_decimal *src, int num, int bit);
int s21_m10(s21_decimal *src);
int s21_div_10_big(s21_big_decimal *src);
int s21_set_bit_in_decimal(s21_decimal *d, size_t n, bool value);
int s21_set_bit_in_decimal_big(s21_big_decimal *d, size_t n, bool value);
void s21_is_greater_perebor(s21_decimal *dst1, s21_decimal *dst2, int *result);
void s21_is_greater_perebor_big(s21_big_decimal *dst1, s21_decimal *dst2,
                                int *result);
void s21_check_1biger2(s21_decimal *dst1, s21_decimal *dst2, int deltaexp,
                       int *result);
void s21_check_1smaller2(s21_decimal *dst1, s21_decimal *dst2, size_t deltaexp,
                         int *result);
void s21_is_equal_zero(s21_decimal *dst1, s21_decimal *dst2, int *result);
int s21_get_big_decimal_digit(s21_big_decimal src, int ind);
void s21_big_decimal_add(s21_big_decimal *src1, s21_big_decimal *src2);
void s21_init_decimal_default(s21_decimal *d);
int s21_init_decimal_copy(s21_decimal *to, s21_decimal from);
int s21_get_sign(s21_decimal d);
// int is_equal(s21_decimal a, s21_decimal b);
int s21_add_for_truncate(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
int s21_sub_for_truncate(s21_decimal value_1, s21_decimal value_2,
                         s21_decimal *result);
int s21_my_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
bool s21_my_get_bit(s21_decimal d, size_t n);
int s21_my_set_bit(s21_decimal *d, size_t n, int value);

#endif