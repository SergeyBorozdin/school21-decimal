#include "s21_decimal.h"

void _rescale(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal_alt alt_value_1 = _convert_std_to_alt(*value_1);
  s21_decimal_alt alt_value_2 = _convert_std_to_alt(*value_2);
  _rescale_alt(&alt_value_1, &alt_value_2);
  *value_1 = _convert_alt_to_std(alt_value_1);
  *value_2 = _convert_alt_to_std(alt_value_2);
}

void _rescale_alt(s21_decimal_alt *alt_value_1, s21_decimal_alt *alt_value_2) {
  s21_decimal_alt ten;
  _null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (!_is_null(*alt_value_1) && !_is_null(*alt_value_2)) {
    if (alt_value_1->exp > alt_value_2->exp) {
      int exp_dif = alt_value_1->exp - alt_value_2->exp;
      for (int i = 0; i < exp_dif; i++)
        _mul_alt(*alt_value_2, ten, alt_value_2);
      if (_last_bit(*alt_value_2) > 95) {
        _rescale_alt_to_smaller(alt_value_1, alt_value_2);
      }
      alt_value_2->exp = alt_value_1->exp;
    } else if (alt_value_2->exp > alt_value_1->exp) {
      _rescale_alt(alt_value_2, alt_value_1);
    }
  } else if (_is_null(*alt_value_1)) {
    alt_value_1->exp = alt_value_2->exp;
  } else {
    alt_value_2->exp = alt_value_1->exp;
  }
}

void _rescale_alt_to_smaller(s21_decimal_alt *alt_value_1,
                             s21_decimal_alt *alt_value_2) {
  int mod1 = 0, mod2 = 0;
  while (_last_bit(*alt_value_2) > 95) {
    mod1 = _div_by_ten(alt_value_1);
    mod2 = _div_by_ten(alt_value_2);
  }
  _bank_rounding(alt_value_1, mod1);
  _bank_rounding(alt_value_2, mod2);
  if (_last_bit(*alt_value_2) > 95) {
    mod1 = _div_by_ten(alt_value_1);
    mod2 = _div_by_ten(alt_value_2);
    _bank_rounding(alt_value_1, mod1);
    _bank_rounding(alt_value_2, mod2);
  }
}

// приводит exp к нулю, нужно для деления
void _rescale_alt_to_zero(s21_decimal_alt *alt_value_1,
                          s21_decimal_alt *alt_value_2) {
  s21_decimal_alt ten;
  _null_decimal_alt(&ten);
  ten.bits[1] = 1;
  ten.bits[3] = 1;
  if (alt_value_1->exp > alt_value_2->exp) {
    alt_value_1->exp -= alt_value_2->exp;
    alt_value_2->exp = 0;
    while (alt_value_1->exp != 0) {
      alt_value_1->exp--;
      _mul_alt(*alt_value_2, ten, alt_value_2);
    }
  } else {
    alt_value_2->exp -= alt_value_1->exp;
    alt_value_1->exp = 0;
    while (alt_value_2->exp != 0) {
      alt_value_2->exp--;
      _mul_alt(*alt_value_1, ten, alt_value_1);
    }
  }
}
