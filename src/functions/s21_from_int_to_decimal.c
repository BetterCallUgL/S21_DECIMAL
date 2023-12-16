#include <stdio.h>

#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;

  if (dst == NULL) {
    result = 1;
  } else {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }

    if (src < 0) {
      dst->bits[3] |= MINUS;
      src = -src;
    }

    dst->bits[0] = (unsigned int)src;
    // for (int j = 0; j < 4; j++) {
    //   printf("bits[%d] - ", j);
    //   for (int i = 31; i >= 0; i--) {
    //     printf("%d", (dst->bits[j] >> i) & 1);
    //   }
    //   printf("\n");
    // }
  }
  return result;
}

// int main() {
//   s21_decimal a;
//   int b = -13277;
//   s21_from_int_to_decimal(b, &a);
// }