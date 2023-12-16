#include <stdio.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

void s21_shift_right(s21_decimal *dst);
void s21_shift_left(s21_decimal *dst);
s21_decimal s21_div_remains(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result);

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  if (s21_is_equal(value_2, (s21_decimal){{0, 0, 0, 0}})) {
    flag = 3;
  } else {
    s21_init_decimal_default(result);
    size_t exp1 = s21_get_exp(value_1), exp2 = s21_get_exp(value_2);
    int sign1 = s21_get_bit(value_1, 128), sign2 = s21_get_bit(value_2, 128);
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    value_1 = s21_div_remains(value_1, value_2, result);
    if (!s21_is_equal(value_1, (s21_decimal){{0, 0, 0, 0}})) {
      s21_decimal buf = {{0, 0, 0, 0}};
      while (s21_mul(value_1, (s21_decimal){{10, 0, 0, 0}}, &buf) == 0 &&
             s21_mul(*result, (s21_decimal){{10, 0, 0, 0}}, &buf) == 0 &&
             !s21_is_equal(value_1, (s21_decimal){{0, 0, 0, 0}}) &&
             (int)(exp1 - exp2) < 28 && s21_get_bit(*result, 96) == 0 &&
             s21_get_bit(*result, 95) == 0 && s21_get_bit(*result, 94) == 0) {
        s21_mul(value_1, (s21_decimal){{10, 0, 0, 0}}, &value_1);
        s21_mul(*result, (s21_decimal){{10, 0, 0, 0}}, result);

        if (s21_is_greater_or_equal(value_1, value_2)) {
          buf = (s21_decimal){{0, 0, 0, 0}};
          value_1 = s21_div_remains(value_1, value_2, &buf);
          s21_add(*result, buf, result);
        }
        exp1++;
      }
    }
    if (s21_is_not_equal(value_1, (s21_decimal){{0, 0, 0, 0}})) {
      flag += s21_bank_rounding_div(value_1, value_2, result);
    }
    if (s21_is_equal(*result, (s21_decimal){{0, 0, 0, 0}}) &&
        exp1 - exp2 > 28) {
      flag = 2;
    } else if ((long int)exp1 - (long int)exp2 < 0) {
      while ((int)(exp1 - exp2) < 0 && s21_get_bit(*result, 96) == 0 &&
             s21_get_bit(*result, 95) == 0 && s21_get_bit(*result, 94) == 0) {
        s21_mul(*result, (s21_decimal){{10, 0, 0, 0}}, result);
        exp1++;
      }
      if ((long int)exp1 - (long int)exp2 < 0) {
        flag = 1;
      }
    } else {
      result->bits[3] += (int)(exp1 - exp2) << 16;
    }
    if (sign1 != sign2) {
      result->bits[3] |= (1 << 31);
    }
  }
  return flag;
}

s21_decimal s21_div_remains(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *result) {
  while (s21_is_greater_or_equal(value_1, value_2)) {
    s21_decimal buf;
    s21_decimal_init(&value_2, &buf);
    int i;
    int flag = 0;
    for (i = 0; s21_is_greater(value_1, buf) && flag == 0; i++) {
      if (s21_get_bit(buf, 96) == 0) {
        s21_shift_left(&buf);
      } else {
        flag = 1;
      }
    }
    if (s21_is_equal(value_1, buf)) {
      s21_sub(value_1, buf, &value_1);
      (flag == 0) ? s21_shift_right(&buf) : 0;
    } else {
      i--;
      (flag == 0) ? s21_shift_right(&buf) : 0;
      s21_sub(value_1, buf, &value_1);
    }
    s21_set_bit(result, (size_t)i, 1);
  }
  return value_1;
}

void s21_shift_right(s21_decimal *dst) {
  int buf = 0;
  int buf2 = 0;
  buf = (dst->bits[2]) % 2;
  dst->bits[2] >>= 1;
  buf2 = dst->bits[1] % 2;
  dst->bits[1] >>= 1;
  dst->bits[1] |= buf << 31;
  dst->bits[0] >>= 1;
  dst->bits[0] |= buf2 << 31;
}

void s21_shift_left(s21_decimal *dst) {
  long unsigned int buf = 0;
  long unsigned int buf2 = 0;
  buf = (long unsigned int)(dst->bits[0]) << 1;
  (dst->bits[0]) <<= 1;
  buf2 = (long unsigned int)(dst->bits[1]) << 1;
  dst->bits[1] = (dst->bits[1] << 1) + (buf >> 32);
  dst->bits[2] = (dst->bits[2] << 1) + (buf2 >> 32);
}

// int main() {
//   s21_decimal b1 = {{0x10, 0x0, 0x0, 0}};
//   s21_decimal b2 = {{0x3, 0, 0, 0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   printf("delimoe\n");
//   s21_print_decimal_by_digits(b1);
//   printf("\n");
//   printf("delitel\n");
//   s21_print_decimal_by_digits(b2);
//   printf("\n");
//   int res = s21_div(b1, b2, &result);
//   printf("chastnoe\n");
//   for (int j = 0; j < 4; j++) {
//     printf("bits[%d] - ", j);
//     for (int i = 31; i >= 0; i--) {
//       printf("%d", (result.bits[j] >> i) & 1);
//     }
//     printf("\n");
//   }
//   s21_print_decimal_by_digits(result);
//   printf("\nres = %d\n", res);
//   return 0;
// }
