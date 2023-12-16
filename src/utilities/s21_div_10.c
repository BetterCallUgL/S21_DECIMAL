#include "s21_utilities.h"

int s21_div_10(s21_decimal* result, int move) {
  int last_num = 0;

  while (move > 0) {
    unsigned long long uns_buffer = result->bits[2];
    // printf("move = %d\n", move);
    for (int j = 2; j >= 0; j--) {
      if (j == 0) {
        last_num = uns_buffer % 10;
        result->bits[j] = uns_buffer / 10;
        // printf("uns = %u\n", uns_buffer);

      } else {
        last_num = uns_buffer % 10;
        result->bits[j] = uns_buffer / 10;
        uns_buffer = last_num * (1 << 31) + (unsigned int)result->bits[j - 1];
      }
    }
    move--;
  }
  return last_num;
}

int s21_div_10_big(s21_big_decimal* src) {
  int last_num = 0;
  unsigned long long uns_buffer = src->bits[6];
  // printf("move = %d\n", move);
  for (int j = 6; j >= 0; j--) {
    if (j == 0) {
      last_num = uns_buffer % 10;
      src->bits[j] = uns_buffer / 10;
      // printf("uns = %u\n", uns_buffer);

    } else {
      last_num = uns_buffer % 10;
      src->bits[j] = uns_buffer / 10;
      uns_buffer = last_num * (1 << 31) + (unsigned int)src->bits[j - 1];
    }
  }
  return last_num;
}