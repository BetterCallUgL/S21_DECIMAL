#include "s21_utilities.h"

int s21_get_bit(s21_decimal d, size_t n) {
  if (!n || n > 128) return -1;
  n--;
  int part_of_decimal = n / 32;
  int part_of_int = n % 32;
  return (d.bits[part_of_decimal] >> part_of_int) % 2;
}

int s21_get_bit_big(s21_big_decimal d, size_t n) {
  if (!n || n > 128) return -1;
  n--;
  int part_of_decimal = n / 32;
  int part_of_int = n % 32;
  return (d.bits[part_of_decimal] >> part_of_int) % 2;
}

int set_bit_in_decimal(s21_decimal *d, size_t n, bool value) {
  if (!n || n > 128 || !d) return 0;
  --n;
  int part_of_decimal = n / 32;
  int part_of_int = n % 32;
  if (value)
    d->bits[part_of_decimal] |= (value << part_of_int);
  else
    d->bits[part_of_decimal] &= ~(value << part_of_int);
  return 1;
}

// int set_bit_in_decimal_big(s21_big_decimal *d, size_t n, bool value) {
//   if (!n || n > 128 || !d) return 0;
//   --n;
//   int part_of_decimal = n / 32;
//   int part_of_int = n % 32;
//   if (value)
//     d->bits[part_of_decimal] |= (value << part_of_int);
//   else
//     d->bits[part_of_decimal] &= ~(value << part_of_int);
//   return 1;
// }

void s21_is_greater_perebor(s21_decimal *dst1, s21_decimal *dst2, int *result) {
  int stop = 1;
  for (int i = 96; i > 0 && stop; i--) {
    if (s21_get_bit(*dst1, i) != s21_get_bit(*dst2, i)) {
      if (s21_get_bit(*dst1, i) > s21_get_bit(*dst2, i)) {
        *result = 1;
        stop = 0;
      } else if (s21_get_bit(*dst1, i) < s21_get_bit(*dst2, i)) {
        *result = -1;
        stop = 0;
      }
    }
  }
}

void s21_is_greater_perebor_big(s21_big_decimal *dst1, s21_decimal *dst2,
                                int *result) {
  int stop = 1;
  for (int i = 96; i > 0 && stop; i--) {
    if (s21_get_bit_big(*dst1, i) != s21_get_bit(*dst2, i)) {
      if (s21_get_bit_big(*dst1, i) > s21_get_bit(*dst2, i)) {
        // printf("i - %d, d1- %d, d2 - %d\n",  i,s21_get_bit_big(*dst1, i),
        // s21_get_bit(*dst2, i));
        *result = 1;
        stop = 0;
      } else if (s21_get_bit_big(*dst1, i) < s21_get_bit(*dst2, i)) {
        *result = -1;
        stop = 0;
      }
    }
  }
}

void s21_check_1biger2(s21_decimal *dst1, s21_decimal *dst2, int deltaexp,
                       int *result) {
  s21_big_decimal *dst = malloc(sizeof(s21_big_decimal));
  s21_big_decimal_init(dst2, dst);
  for (int i = 0; i < deltaexp; i++) {
    s21_multiply_by_ten(dst);
  }
  int flag = 1;
  for (int i = 6; i > 2; i--) {
    if (dst->bits[i]) flag = 0;
  }
  if (flag) {
    s21_is_greater_perebor_big(dst, dst1, result);
  }
  // printf("%d\n", *result);
  free(dst);
}

void s21_check_1smaller2(s21_decimal *dst1, s21_decimal *dst2, size_t deltaexp,
                         int *result) {
  s21_big_decimal *dst = malloc(sizeof(s21_big_decimal));
  s21_big_decimal_init(dst1, dst);
  for (size_t i = 0; i < deltaexp; i++) {
    s21_multiply_by_ten(dst);
  }
  for (int i = 6; i > 2; i--) {
    if (dst->bits[i]) *result = 1;
  }
  if (!*result) {
    s21_is_greater_perebor_big(dst, dst2, result);
  }
  free(dst);
}

void s21_is_equal_zero(s21_decimal *dst1, s21_decimal *dst2, int *result) {
  for (int i = 0; i < 4; i++) {
    if (dst1->bits[i] == 0 && dst2->bits[i] == 0) {
      *result = *result + 1;
    }
  }
  *result = (*result == 3) ? 1 : 0;
}
