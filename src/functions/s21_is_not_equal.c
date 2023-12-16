#include <stdio.h>

#include "../s21_decimal.h"
#include "../utilities/s21_utilities.h"

int s21_is_not_equal(s21_decimal dst1, s21_decimal dst2) {
  int result = 0;
  // pervoe > 0, vtoroe <0 or pervoe < 0, vtoroe >0
  if ((!s21_get_bit(dst1, 128) && s21_get_bit(dst2, 128)) ||
      (s21_get_bit(dst1, 128) && !s21_get_bit(dst2, 128))) {
    s21_is_equal_zero(&dst1, &dst2, &result);
    result = !result;
    // oba +
  } else if (!s21_get_bit(dst1, 128) && !s21_get_bit(dst2, 128)) {
    size_t exp1 = s21_get_exp(dst1), exp2 = s21_get_exp(dst2);
    printf("exp1=%ld, exp2=%ld\n", exp1, exp2);
    if (exp1 == exp2) {
      s21_is_greater_perebor(&dst1, &dst2, &result);
    } else if (exp1 > exp2) {
      s21_check_1biger2(&dst1, &dst2, exp1 - exp2, &result);
    } else if (exp1 < exp2) {
      s21_check_1smaller2(&dst1, &dst2, exp2 - exp1, &result);
    }
    result = (0 == result) ? 0 : 1;
    // oba -
  } else if (s21_get_bit(dst1, 128) && s21_get_bit(dst2, 128)) {
    size_t exp1 = s21_get_exp(dst1), exp2 = s21_get_exp(dst2);
    // printf("exp1=%ld, exp2=%ld\n", exp1, exp2);
    if (exp1 == exp2) {
      s21_is_greater_perebor(&dst1, &dst2, &result);
    } else if (exp1 > exp2) {
      s21_check_1smaller2(&dst2, &dst1, exp1 - exp2, &result);
    } else if (exp1 < exp2) {
      s21_check_1biger2(&dst2, &dst1, exp2 - exp1, &result);
    }
    result = (0 == result) ? 0 : 1;
  }
  return result;
}

// int main() {
//   s21_decimal b1 = {{1, 0, 0, 0}};
//   s21_decimal b2 = {{0xA, 0, 0, 0 | (1 << 16)}};
//   for (int j = 0; j < 4; j++) {
//     printf("bits[%d] - ", j);
//     for (int i = 31; i >= 0; i--) {
//       printf("%d", (b1.bits[j] >> i) & 1);
//     }
//     printf("\n");
//   }
//   for (int j = 0; j < 4; j++) {
//     printf("bits[%d] - ", j);
//     for (int i = 31; i >= 0; i--) {
//       printf("%d", (b2.bits[j] >> i) & 1);
//     }
//     printf("\n");
//   }
//   int res = s21_is_not_equal(b1, b2);
//   printf("\nres = %d\n", res);
//   return 0;
// }
