#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  char line[40];
  unsigned int mantissa = 0;
  char exp = 0;

  // check if src isnan or isinf
  if (isnan(src) || isinf(src) || src > 1e29 || dst == NULL) {
    result = 1;
  } else {
    // filling decimal with zeros.
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    // check if neg
    if (src < 0) {
      dst->bits[3] |= MINUS;
      src = -src;
    }
    while ((int)src < 1000000) {
      exp++;
      src *= 10;
    }
    /* check if src is too small
    (28 from condition and 7 more cuz we multiplied the num 7 times by 10) */
    if (exp > 28 + 7) {
      result = 1;
    } else {
      // main func
      sprintf(line, "%f", src);
      int index = 0;

      // mantissa we are going to fill
      for (; index < 7; index++) {
        mantissa = mantissa * 10 + (int)(line[index] - '0');
      }
      // if the num is bigger than 10mil
      if (line[index] != '.') {
        // rounding
        if ((int)(line[index] - '0') > 0.5) {
          mantissa += 1;
        }
        while (line[index] != '.') {
          mantissa *= 10;
          index++;
        }
      } else {
        // rounding
        if ((int)(line[index + 1] - '0') > 0.5) {
          mantissa++;
        }
      }
      // printf("%d\n%d\n", mantissa, exp);
    }

    // filling the decimal
    dst->bits[0] = mantissa;
    for (int i = 7; i >= 0; i--) {
      unsigned int bit = (exp >> i) & 1;
      dst->bits[3] |= bit << (16 + i);
    }

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
//   float a = -0.0005045;
//   s21_decimal b;
//   if (s21_from_float_to_decimal(a, &b)) {
//     perror("ERROR!");
//   }
// }