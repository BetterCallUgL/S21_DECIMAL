#include "../utilities/s21_utilities.h"

int s21_floor(s21_decimal value, s21_decimal* result) {
  int e_code = ERROR;
  int exp = s21_get_exp(value);
  if (&value != result) s21_init_decimal_copy(result, value);
  if ((exp >= 0 && exp <= 28) || !result) {
    if (!exp)
      e_code = OK;
    else if (!s21_get_sign(value))
      e_code = s21_truncate(value, result);
    else {
      s21_decimal tmp;  // one;
      s21_init_decimal_default(&tmp);
      if (value.bits[0] || value.bits[1] || value.bits[2])
        s21_sub_for_truncate(value, one, &tmp);
      e_code = s21_truncate(tmp, result);
    }
  } else
    e_code = ERROR;
  return e_code;
}
/*
int main() {
    s21_decimal number;
  init_decimal_default(&number);
    //
  //
  //
  //    FLOOR_TEST
  //
  //
  //

  // 1010011101 01000010101101100101100010010001
  // 01110011000101100101111010101001
  //  -12345678912345678912345
  number.bits[0] = 0b01110011000101011001101101011001;
  number.bits[1] = 0b01000010101101100101100010010001;
  number.bits[2] = 0b1010011101;
  number.bits[3] = 0b101 << 16;
  set_bit(&number, 127, 1);

  printf("*********FLOOR*******MINUS*****CASE*****\n");
  if (s21_floor(number, &number) == OK) {
    for (int j = 0; j < 4; j++) {
      printf("INT*****bits[%d] - ", j);
      printf("%u", number.bits[j]);
      printf("\n");
    }
    // rigth - 10001001000100001000011110100 11000000001000111011011011010010
    // 1101101101001101101001011 10101100110100000101111100010110 //
    // 123456789123456790 1 - 10101100110100000101111100010110 0 -
    // 10101100110100000101111100010101
    printf("LL RES - %u\n%u\n%u\nLL KEY - %u\n%u\n%u", number.bits[0],
           number.bits[1], number.bits[2], 0b11000000001000111011011011010010,
           0b10001001000100001000011110100, 0);
  }
  // 1010011101 01000010101101100101100010010001
  // 01110011000101100101111010101001
  //  12345678912345678962345
  number.bits[0] = 0b01110011000101100101111010101001;
  number.bits[1] = 0b01000010101101100101100010010001;
  number.bits[2] = 0b1010011101;
  number.bits[3] = 0b101 << 16;

  if (s21_floor(number, &number) == OK) {
    for (int j = 0; j < 4; j++) {
      printf("INT*****bits[%d] - ", j);
      printf("%u", number.bits[j]);
      printf("\n");
    }
    // 1101101101001101101001011 10101100110100000101111100010101
    // 1 - 1101101101001101101001011
    // 0 - 10101100110100000101111100010101
    // 123456789123456789
    printf("LL RES - %u\n%u\n%u\nLL KEY - %u\n%u\n%u", number.bits[0],
           number.bits[1], number.bits[2], 0b10101100110100000101111100010101,
           0b1101101101001101101001011, 0);
  }

  return 0;
}*/