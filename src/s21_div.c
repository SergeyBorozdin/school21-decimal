#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  if (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0) {
    return_code = 3;
  } else if (value_1.bits[0] == 0 && value_1.bits[1] == 0 &&
             value_1.bits[2] == 0) {
    _init_decimal(result);
  } else {
    s21_decimal_alt alt_value_1 = _convert_std_to_alt(value_1);
    s21_decimal_alt alt_value_2 = _convert_std_to_alt(value_2);
    s21_decimal_alt alt_result;
    _null_decimal_alt(&alt_result);
    while (alt_value_1.bits[0] == 0 && alt_value_2.bits[0] == 0) {
      _right_shift(&alt_value_1);
      _right_shift(&alt_value_2);
    }
    return_code = _div_alt(alt_value_1, alt_value_2, &alt_result);
    *result = _convert_alt_to_std(alt_result);
  }
  return return_code;
}
