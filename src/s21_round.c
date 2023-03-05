#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *res) {
  int return_code = 0;
  if (res) {
    s21_decimal_alt alt_value = _convert_std_to_alt(value);
    int mod = 0;
    while (alt_value.exp > 0) mod = _div_by_ten(&alt_value);
    if (mod >= 5) {
      s21_decimal_alt one;
      _null_decimal_alt(&one);
      one.bits[0] = 1;
      one.sign = alt_value.sign;
      _add_alt(one, alt_value, &alt_value);
    }
    *res = _convert_alt_to_std(alt_value);
  } else {
    return_code = 1;
  }
  return return_code;
}
