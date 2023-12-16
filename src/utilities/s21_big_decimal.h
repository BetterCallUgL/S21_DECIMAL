#ifndef S21_BIG_DECIMAL_H
#define S21_BIG_DECIMAL_H
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

/*void s21_big_decimal_init(s21_decimal* src, s21_big_decimal* dst);
void s21_multiply_by_ten(s21_big_decimal* src);*/
// int s21_get_bit(s21_decimal d, size_t n);
// size_t s21_get_exp(s21_decimal d);
int s21_get_bit_big(s21_big_decimal d, size_t n);
int set_bit_in_decimal(s21_decimal* d, size_t n, bool value);
int set_bit_in_decimal_big(s21_big_decimal* d, size_t n, bool value);

#endif