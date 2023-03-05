#include "s21_decimal.h"

int _mul_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result) {
  int return_code = 0;
  _null_decimal_alt(alt_result);
  if (!_is_null(alt_value_1) && !(_is_null(alt_value_2))) {
    for (int i = 0; i < 192; i++) {
      if (alt_value_2.bits[i] == 1)
        _add_alt(*alt_result, alt_value_1, alt_result);
      _left_shift(&alt_value_1);
    }
    alt_result->exp = alt_value_1.exp + alt_value_2.exp;
    alt_result->sign = alt_value_1.sign ^ alt_value_2.sign;
    if (_last_bit(*alt_result) > 95 || alt_result->exp > 28) {
      int mod = 0;
      while (alt_result->exp > 0 &&
             (_last_bit(*alt_result) > 95 || alt_result->exp > 28)) {
        if (alt_result->exp == 0) break;
        mod = _div_by_ten(alt_result);
      }
      if (alt_result->exp > 0)
        _bank_rounding(alt_result, mod);
      else
        return_code = 1;
    }
    if (_is_null(*alt_result)) return_code = 2;
  }
  return return_code;
}
