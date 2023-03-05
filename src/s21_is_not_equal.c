#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  int equality = s21_is_equal(a, b);
  int not_equal;
  if (equality) {
    not_equal = 0;
  } else {
    not_equal = 1;
  }
  return not_equal;
}
