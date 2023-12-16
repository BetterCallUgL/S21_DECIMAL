#include "s21_utilities.h"
#include "stdio.h"

void s21_decimal_print(s21_decimal* dst) {
  for (int j = 0; j < 4; j++) {
    printf("bits[%d] - ", j);
    for (int i = 31; i >= 0; i--) {
      printf("%d", (dst->bits[j] >> i) & 1);
    }
    printf("\n");
  }
}

void s21_big_decimal_print(s21_big_decimal* dst) {
  for (int j = 0; j < 8; j++) {
    printf("bits[%d] - ", j);
    for (int i = 31; i >= 0; i--) {
      printf("%d", (dst->bits[j] >> i) & 1);
    }
    printf("\n");
  }
}