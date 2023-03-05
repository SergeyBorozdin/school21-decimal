#include "s21_decimal.h"

int s21_is_less(s21_decimal a, s21_decimal b) {
  int less = 0;
  int equal = s21_is_equal(a, b);
  if (equal == 0) {
    less = s21_is_greater(a, b) ? 0 : 1;
  }
  return less;
}
