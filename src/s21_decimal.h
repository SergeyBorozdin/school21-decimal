#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT_BIT_INT 32
#define BIT 8
#define SIZE_BITS 4
#define TRUE 1
#define FALSE 0
#define BIT_SIZE 4
#define NUM_255 255

#define S21_MAX_UINT 4294967295
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

typedef struct {
  unsigned int bits[SIZE_BITS];
} s21_decimal;

/*
- bits[0] младшие 32 бита
- bits[1] средние 32 бита
- bits[2] старшие 32 бита
- bits[3] содержит коэффициент масштабирования и знак
=======================================================

- Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю
- Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
указывает степень 10 для разделения целого числа
- Биты с 24 по 30 не используются и должны быть равны нулю
- Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный
*/

typedef union {
  float flt;
  unsigned int bits;
} lens_t;

/*
    ===========================================
    Арифметические операторы
*/

// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление /
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Остаток от деления Mod
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*
    ===========================================
    Операторы сравнение, Возвращаемое значение ( 0-FALSE, 1-TRUE)
*/
int s21_is_less(s21_decimal, s21_decimal);           // Меньше <
int s21_is_less_or_equal(s21_decimal, s21_decimal);  // Меньше равно <=
int s21_is_greater(s21_decimal, s21_decimal);        // больше >
int s21_is_greater_or_equal(s21_decimal, s21_decimal);  // Больше или равно >=
int s21_is_equal(s21_decimal, s21_decimal);      // равно ==
int s21_is_not_equal(s21_decimal, s21_decimal);  // Не равно !=

/*
    ===========================================
    функции преобразователи, возращает код ошибки (0-ok, 1-ошибки)
*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);      // из int
int s21_from_float_to_decimal(float src, s21_decimal *dst);  // из float
int s21_from_decimal_to_int(s21_decimal src, int *dst);      // в int
int s21_from_decimal_to_float(s21_decimal src, float *dst);  // в float

/*
    ==========================================
    другие функции, возращает код ошибки (0-ok, 1-ошибки)
*/
// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result);

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули
int s21_truncate(s21_decimal value, s21_decimal *result);

//  результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result);

/*
    =========================================
    вспомогательные функции
*/
// Проверить знак переменной если >0 то вернет 0, а если <0 то 1
int is_int_negative(int value);

// Установить бит под номером BitNumber в значение 1 в переменной value
void set_1_bit(unsigned int *value, int BitNumber);

/*
    function set_1_bit
    Установить бит под номером BitNumber в значение 1 в переменной value
*/

/*
    функции из видео про работу с битами
*/
// 250 интов  это 205 * 32 бита = 8000 бит

int get_row(int bit);
int get_col(int bit);

bool is_set_bit(int *bit_vector, int index);
void set_bit(int *bit_vector, int index);
bool inverse_bit(int *bit_vector, int index);
bool reset_bit(int *bit_vector, int index);

/*
    функции для печати двоичного содержимого int decimal
*/
int print_bit(int a);
void print_bit_int(int a);
void print_bit_dec(int a, int b, int c, int d);

#endif  // SRC_S21_DECIMAL_H_
