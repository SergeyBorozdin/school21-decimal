#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  s21_decimal_alt alt_value_1 = _convert_std_to_alt(value_1);
  s21_decimal_alt alt_value_2 = _convert_std_to_alt(value_2);
  s21_decimal_alt alt_result;
  _null_decimal_alt(&alt_result);
  return_code = _mul_alt(alt_value_1, alt_value_2, &alt_result);
  *result = _convert_alt_to_std(alt_result);
  return return_code;
}
