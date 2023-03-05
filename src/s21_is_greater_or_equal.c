#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int res = 0;
  res = s21_is_equal(a, b);
  if (res == 0) res = s21_is_greater(a, b);
  return res;
}
