#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = 0;
  _rescale(&value_1, &value_2);
  s21_decimal_alt alt_value_1 = _convert_std_to_alt(value_1);
  s21_decimal_alt alt_value_2 = _convert_std_to_alt(value_2);
  s21_decimal_alt alt_result;
  _null_decimal_alt(&alt_result);
  if (alt_value_1.sign == alt_value_2.sign) {
    if ((s21_is_greater_or_equal(value_1, value_2) && !alt_value_1.sign) ||
        (s21_is_less_or_equal(value_1, value_2) && alt_value_1.sign)) {
      return_code = _sub_alt(alt_value_1, alt_value_2, &alt_result);
    } else {
      alt_value_1.sign = alt_value_1.sign ^ 1;
      alt_value_2.sign = alt_value_2.sign ^ 1;
      return_code = _sub_alt(alt_value_2, alt_value_1, &alt_result);
    }
    alt_result.sign = alt_value_1.sign;
  } else {
    alt_value_2.sign = alt_value_2.sign ^ 1;
    value_2 = _convert_alt_to_std(alt_value_2);
    return_code = s21_add(value_1, value_2, result);
    alt_result = _convert_std_to_alt(*result);
  }
  alt_result.exp = alt_value_1.exp;
  *result = _convert_alt_to_std(alt_result);
  return return_code;
}
