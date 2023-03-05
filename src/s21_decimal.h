#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MINUS_SIGN 2147483648
#define UINT_MAX 4294967295

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  bool bits[192];
  bool sign;
  int exp;
} s21_decimal_alt;

typedef enum {
  OPERATION_OK = 0,
  NUMBER_TOO_BIG,
  NUMBER_TOO_SMALL,
  DIVISION_BY_ZERO
} operation_result;

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_result;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_round(s21_decimal value, s21_decimal *res);
int s21_floor(s21_decimal value, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *res);
int s21_truncate(s21_decimal value, s21_decimal *res);

int _sub_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _add_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _mul_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _div_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);
int _mod_alt(s21_decimal_alt alt_value_1, s21_decimal_alt alt_value_2,
             s21_decimal_alt *alt_result);

bool _get_bit_int(unsigned int num, int pos);
void _right_shift(s21_decimal_alt *alt);
void _left_shift(s21_decimal_alt *alt);
bool _get_sign_std(s21_decimal dec);
int _get_exp_std(s21_decimal dec);
void _null_decimal_alt(s21_decimal_alt *alt);
s21_decimal_alt _convert_std_to_alt(s21_decimal std);
s21_decimal _convert_alt_to_std(s21_decimal_alt alt);
void _rescale(s21_decimal *value_1, s21_decimal *value_2);
void _rescale_alt(s21_decimal_alt *alt_value_1, s21_decimal_alt *alt_value_2);
void _rescale_alt_to_smaller(s21_decimal_alt *alt_value_1,
                             s21_decimal_alt *alt_value_2);
void _init_decimal(s21_decimal *decimal);
int _div_by_ten(s21_decimal_alt *alt);
bool _compare_bits(s21_decimal_alt alt1, s21_decimal_alt alt2);
bool _is_null(s21_decimal_alt alt);
int _last_bit(s21_decimal_alt alt);
void _bank_rounding(s21_decimal_alt *alt, int mod);
void _align(s21_decimal_alt *alt1, s21_decimal_alt *alt2);
void _rescale_alt_to_zero(s21_decimal_alt *alt_value_1,
                          s21_decimal_alt *alt_value_2);
s21_decimal_alt _div_with_modulo(s21_decimal_alt alt_value_1,
                                 s21_decimal_alt alt_value_2,
                                 s21_decimal_alt *alt_result);
void _truncate_alt(s21_decimal_alt *alt_value);
void _set_minus(s21_decimal *dst);

s21_decimal_alt _convert_int_to_alt(unsigned long int number);
s21_decimal _convert_int_to_std(unsigned long int number);

#endif  // SRC_S21_DECIMAL_H_
