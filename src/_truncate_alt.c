#include "s21_decimal.h"

void _truncate_alt(s21_decimal_alt *alt_value) {
  while (alt_value->exp > 0) _div_by_ten(alt_value);
}
