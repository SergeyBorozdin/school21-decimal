#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int equal = 1;
  int zero_sign = 0;
  if ((a.bits[0] + a.bits[1] + a.bits[2]) == 0 &&
      (b.bits[0] + b.bits[1] + b.bits[2]) == 0) {
    zero_sign = 1;
  }
  bool aSign = _get_sign_std(a);
  bool bSign = _get_sign_std(b);
  if (zero_sign) {
    equal = 1;
  } else if (aSign != bSign) {
    equal = 0;
  } else {
    _rescale(&a, &b);
    for (register int i = 0; i <= 2; i++) {
      if (a.bits[i] != b.bits[i]) {
        equal = 0;
        break;
      }
    }
  }
  return equal;
}
