#include "s21_decimal.h"

int _add_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result) {
  int return_code = 0;
  bool t_bit = 0;  // бит переноса
  _null_decimal_alt(alt_result);
  for (int i = 0; i < 192; i++) {
    alt_result->bits[i] = (alt_value_1.bits[i] ^ alt_value_2.bits[i]) ^ t_bit;
    if ((alt_value_1.bits[i] & alt_value_2.bits[i]) ||
        (alt_value_1.bits[i] & t_bit) || (alt_value_2.bits[i] & t_bit))
      t_bit = 1;
    else
      t_bit = 0;
  }
  alt_result->exp = alt_value_1.exp;
  alt_result->sign = alt_value_1.sign;
  if (_last_bit(*alt_result) > 95) {
    if (alt_result->exp <= 0) {
      return_code = 1;
    } else {
      int mod = _div_by_ten(alt_result);
      _bank_rounding(alt_result, mod);
    }
  }
  return return_code;
}
