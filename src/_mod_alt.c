#include "s21_decimal.h"

int _mod_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result) {
  int return_code = 0;
  bool sign = alt_value_1.sign;
  alt_value_1.sign = 0;
  alt_value_2.sign = 0;
  s21_decimal_alt factor;
  _div_alt(alt_value_1, alt_value_2, &factor);
  _truncate_alt(&factor);
  _mul_alt(alt_value_2, factor, &factor);
  _rescale_alt(&alt_value_1, &factor);
  _sub_alt(alt_value_1, factor, alt_result);
  alt_result->exp = factor.exp;
  if (_last_bit(*alt_result) > 95) _truncate_alt(alt_result);
  if (_last_bit(*alt_result) > 95) return_code = 1;
  alt_result->sign = sign;
  return return_code;
}
