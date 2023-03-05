#include "s21_decimal.h"

int _sub_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result) {
  int return_code = 0;
  bool t_bit = 0;
  for (int i = 0; i < 192; i++) {
    alt_result->bits[i] = alt_value_1.bits[i] ^ alt_value_2.bits[i] ^ t_bit;
    if (alt_value_1.bits[i] == 0 && alt_value_2.bits[i] == 1)
      t_bit = 1;
    else if (alt_value_1.bits[i] == 1 && alt_value_2.bits[i] == 0)
      t_bit = 0;
  }
  return return_code;
}
