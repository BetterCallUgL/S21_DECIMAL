#include "s21_utilities.h"

int s21_m10(s21_decimal* src) {
  long int buf1 = 0;
  long int buf2 = 0;
  buf1 = src->bits[0] * 10;
  src->bits[0] = (int)buf1;
  buf2 = (buf1 >> 32) + src->bits[1] * 10;
  src->bits[1] = (int)buf2;
  buf1 = (buf2 >> 32) + src->bits[2] * 10;
  src->bits[1] = (int)buf1;
  return buf1 >> 32;
}