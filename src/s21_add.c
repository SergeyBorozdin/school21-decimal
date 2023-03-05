#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  _rescale(&value_1, &value_2);
  s21_decimal_alt alt_value_1 = _convert_std_to_alt(value_1);
  s21_decimal_alt alt_value_2 = _convert_std_to_alt(value_2);
  s21_decimal_alt alt_result;
  _null_decimal_alt(&alt_result);
  if (alt_value_1.sign == alt_value_2.sign) {
    return_code = _add_alt(alt_value_1, alt_value_2, &alt_result);
  } else {
    if (alt_value_1.sign) {
      alt_value_1.sign = 0;
      value_1 = _convert_alt_to_std(alt_value_1);
      return_code = s21_sub(value_2, value_1, result);
      alt_result = _convert_std_to_alt(*result);
    } else {
      alt_value_2.sign = 0;
      value_2 = _convert_alt_to_std(alt_value_2);
      return_code = s21_sub(value_1, value_2, result);
      alt_result = _convert_std_to_alt(*result);
    }
  }
  *result = _convert_alt_to_std(alt_result);
  return return_code;
}
