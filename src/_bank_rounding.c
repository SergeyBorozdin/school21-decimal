#include "s21_decimal.h"

// деление числа на 10
// возращает остаток от деления числа на 10
int _div_by_ten(s21_decimal_alt *alt) {
  s21_decimal_alt result;
  _null_decimal_alt(&result);
  int exp = alt->exp;
  int sign = alt->sign;
  result.sign = 0;
  result.exp = 0;
  s21_decimal_alt ten;
  _null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  s21_decimal_alt modulo = _div_with_modulo(*alt, ten, alt);
  int res = _convert_alt_to_std(modulo).bits[0];
  alt->exp = exp - 1;
  alt->sign = sign;
  return res;
}

void _bank_rounding(s21_decimal_alt *alt, int mod) {
  if ((mod == 5 && alt->bits[0]) || mod > 5) {
    s21_decimal_alt one;
    _null_decimal_alt(&one);
    one.bits[0] = 1;
    one.exp = alt->exp;
    one.sign = alt->sign;
    _add_alt(*alt, one, alt);
    if (_last_bit(*alt) > 95) {
      _sub_alt(*alt, one, alt);
      mod = _div_by_ten(alt);
      _bank_rounding(alt, mod);
    }
  }
}
