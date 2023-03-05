#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *res) {
  int return_code = 0;
  if (res) {
    s21_decimal_alt alt_value = _convert_std_to_alt(value);
    _truncate_alt(&alt_value);
    if (alt_value.sign &&
        s21_is_not_equal(_convert_alt_to_std(alt_value), value)) {
      s21_decimal_alt one;
      _null_decimal_alt(&one);
      one.bits[0] = 1;
      one.sign = 1;
      _add_alt(one, alt_value, &alt_value);
    }
    *res = _convert_alt_to_std(alt_value);
  } else {
    return_code = 1;
  }
  return return_code;
}
