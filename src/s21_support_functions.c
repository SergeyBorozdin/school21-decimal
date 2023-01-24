#include "s21_decimal.h"

/*
    function is_int_negative
    Проверить знак переменной value
    Если >0 то вернет 0, а если <0 то 1
*/
int is_int_negative(int value) {
  int sign = 0;
  if (value < 0) sign = 1;
  return sign;
}

/*
    функкции из видео для работы с битами

*/

// проверка бита
bool is_set_bit(unsigned int *bit_vector, int index) {
  int index_row = get_row(index);
  int index_col = get_col(index);
  return (bit_vector[index_row] & (1 << index_col)) != 0;
}

// установка бита в 1
void set_bit(unsigned int *bit_vector, int index) {
  int index_row = get_row(index);
  int index_col = get_col(index);
  bit_vector[index_row] |= 1 << index_col;
}

// инверсия бита
bool inverse_bit(int *bit_vector, int index) {
  int index_row = get_row(index);
  int index_col = get_col(index);
  return bit_vector[index_row] ^= 1 << index_col;
}

// установкака бита в 0
bool reset_bit(int *bit_vector, int index) {
  int index_row = get_row(index);
  int index_col = get_col(index);
  return bit_vector[index_row] &= ~(1 << index_col);
}

// возвращает номер строки в битовом векторе
int get_row(int bit) { return (int)floor(bit >> 5); }

// возвращает номер столбца в битовом векторе
int get_col(int bit) { return bit % 32; }

/*
    функции для печати битов инта, децимал
    =====================================
*/

// вспомогательная функция для печати
int print_bit(unsigned int a) {
  int count = 0;
  char bit_int[COUNT_BIT_INT];
  unsigned int *pa = &a;
  int i = 0;
  for (; i != COUNT_BIT_INT; i++) {
    ++count;
    if (is_set_bit(pa, i)) {
      bit_int[i] = '1';
    } else {
      bit_int[i] = '0';
    }
  }
  bit_int[i] = '\0';
  for (int j = COUNT_BIT_INT; j != -1; j--) {
    printf("%c", bit_int[j]);
  }
  return count;
}

// печатает инт
void print_bit_int(int a) {
  int count = 0;
  count += print_bit(a);
  printf("\ncount_bit - %d\n", count);
}

// печатает децимал от инта
void print_bit_dec(int a, int b, int c, int d) {
  int count = 0;
  count += print_bit(d);
  printf(" | ");
  count += print_bit(c);
  printf(" | ");
  count += print_bit(b);
  printf(" | ");
  count += print_bit(a);
  printf("\ncount_bit - %d\n", count);
}

// конветация к десятичной
int s21_10_conv(s21_decimal value) {
  int result = 0;
  int power = 1;
  for (int i = 16; i < 21; i++, power = power * 2)
    if (is_set_bit(&value.bits[3], i)) {
      result = result + power;
    }
  return result;
}
