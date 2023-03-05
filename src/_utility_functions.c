#include "s21_decimal.h"

bool _get_bit_int(unsigned int num, int pos) { return (num >> pos) & 1; }

// сдвиг вправо для альтернативного децимала
void _right_shift(s21_decimal_alt *alt) {
  for (int i = 0; i < 191; i++) alt->bits[i] = alt->bits[i + 1];
  alt->bits[191] = 0;
}

// сдвиг влево для альтернативного децимала
// нужно при умножении
void _left_shift(s21_decimal_alt *alt) {
  for (int i = 191; i > 0; i--) alt->bits[i] = alt->bits[i - 1];
  alt->bits[0] = 0;
}

bool _get_sign_std(s21_decimal dec) { return _get_bit_int(dec.bits[3], 31); }

int _get_exp_std(s21_decimal dec) { return (dec.bits[3] % 2147483648) >> 16; }

void _null_decimal_alt(s21_decimal_alt *alt) {
  alt->sign = 0;
  alt->exp = 0;
  for (int i = 0; i < 192; i++) alt->bits[i] = 0;
}

void _init_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

// сравнение битов первого и второго альтернативного децимала
// не учитывает экспоненту
// возвращает 1, если первое число больше или равно второму
// 0 если второе число больше первого
bool _compare_bits(s21_decimal_alt alt1, s21_decimal_alt alt2) {
  int i = 191;
  while (i >= 0 && alt1.bits[i] == alt2.bits[i]) {
    i--;
  }
  return i == -1 ? 1 : alt1.bits[i];
}

// равен ли альтернативный децимал 0
bool _is_null(s21_decimal_alt alt) {
  bool result = 0;
  for (int i = 0; i < 192; i++) result += alt.bits[i];
  return !result;
}

// где находится самый левый единичный бит?
int _last_bit(s21_decimal_alt alt) {
  int i = -1;
  if (!_is_null(alt)) {
    for (i = 191; i >= 0; i--)
      if (alt.bits[i] == 1) break;
  }
  return i;
}

// "выравнивание" чисел
// нужно в делении
// превращает, например, 1001 и 10 в 1001 и 1000
// но 1001 и 11 в 1001 и 110
// по совершенно непонятным мне причинам не работает с div_by_ten
void _align(s21_decimal_alt *alt_value_1, s21_decimal_alt *alt_value_2) {
  if (!_is_null(*alt_value_1) && !_is_null(*alt_value_2)) {
    int l1 = _last_bit(*alt_value_1);
    int l2 = _last_bit(*alt_value_2);
    while (_last_bit(*alt_value_1) != _last_bit(*alt_value_2))
      if (_compare_bits(*alt_value_1, *alt_value_2))
        _left_shift(alt_value_2);
      else
        _left_shift(alt_value_1);
    if (!_compare_bits(*alt_value_1, *alt_value_2)) _left_shift(alt_value_1);
    if (alt_value_1->bits[0] == 0 && alt_value_2->bits[0] == 0 &&
        _last_bit(*alt_value_1) > l1 && _last_bit(*alt_value_2) > l2) {
      _right_shift(alt_value_1);
      _right_shift(alt_value_2);
    }
  }
}
