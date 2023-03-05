#include "s21_decimal.h"

int _div_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result) {
  s21_decimal_alt ten;
  _null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  _null_decimal_alt(alt_result);
  int return_code = 0;
  bool sign = alt_value_1.sign ^ alt_value_2.sign;
  alt_value_1.sign = 0;
  alt_value_2.sign = 0;

  _rescale_alt_to_zero(&alt_value_1, &alt_value_2);
  s21_decimal_alt modulo;
  _null_decimal_alt(&modulo);
  modulo = _div_with_modulo(alt_value_1, alt_value_2, &alt_value_1);
  int exp = 0;
  int status = 0;
  while (!_is_null(alt_value_1) || !_is_null(modulo)) {
    exp++;
    _mul_alt(modulo, ten, &modulo);
    _mul_alt(*alt_result, ten, alt_result);
    status = _add_alt(*alt_result, alt_value_1, alt_result);
    modulo = _div_with_modulo(modulo, alt_value_2, &alt_value_1);
    if (status == 1) break;
  }
  int mod;
  if (status == 1) {
    mod = _div_by_ten(alt_result);
    while (_last_bit(*alt_result) > 95 && exp > 0) {
      mod = _div_by_ten(alt_result);
      exp--;
    }
    _bank_rounding(alt_result, mod);
    exp--;
  }
  alt_result->exp = exp - 1;
  mod = 10;
  while (alt_result->exp > 28) mod = _div_by_ten(alt_result);
  if (_is_null(*alt_result))
    return_code = 2;
  else if (mod != 10)
    _bank_rounding(alt_result, mod);
  if (_last_bit(*alt_result) > 95) return_code = 1;
  alt_result->sign = sign;
  return return_code;
}

s21_decimal_alt _div_with_modulo(s21_decimal_alt alt_value_1,
                                 s21_decimal_alt alt_value_2,
                                 s21_decimal_alt *alt_result) {
  int denominator_left_bit = _last_bit(alt_value_2);
  s21_decimal_alt modulo;
  _null_decimal_alt(&modulo);
  _null_decimal_alt(alt_result);
  if (_compare_bits(alt_value_1, alt_value_2)) {
    _align(&alt_value_1, &alt_value_2);
  }
  for (int i = 0; i < 191; i++) {
    if (_compare_bits(alt_value_1, alt_value_2)) {
      _sub_alt(alt_value_1, alt_value_2, &alt_value_1);
      alt_result->bits[0] = 1;
    }
    if (_last_bit(alt_value_2) <= denominator_left_bit) break;
    if (_last_bit(alt_value_2) > denominator_left_bit)
      _right_shift(&alt_value_2);
    _left_shift(alt_result);
  }
  return alt_value_1;
}
