#include "s21_decimal.h"

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  res = s21_is_equal(a, b);
  if (res == 0) res = s21_is_less(a, b);
  return res;
}
