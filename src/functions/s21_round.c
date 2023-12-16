#include "../utilities/s21_utilities.h"

int s21_round(s21_decimal value, s21_decimal* result) {
  int e_code = ERROR;
  int exp = s21_get_exp(value);
  if (&value != result) s21_init_decimal_copy(result, value);
  if ((exp >= 0 && exp <= 28) || !result) {
    if (!exp)
      e_code = OK;
    else {
      s21_decimal tmp;
      s21_init_decimal_default(&tmp);
      if (s21_get_sign(value))
        s21_sub_for_truncate(value, half, &tmp);
      else
        s21_add_for_truncate(value, half, &tmp);
      printf("%u*****%u*****%u******%u\n", value.bits[0], value.bits[1],
             value.bits[2], value.bits[3]);
      printf("%u*****%u*****%u******%u\n", tmp.bits[0], tmp.bits[1],
             tmp.bits[2], tmp.bits[3]);
      e_code = s21_truncate(tmp, result);
    }
  } else
    e_code = ERROR;

  return e_code;
}