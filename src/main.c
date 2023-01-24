#include "s21_decimal.h"

int main() {
  s21_decimal b;
  int a = 2147483647;
  s21_from_int_to_decimal(a, &b);
  int dec1 = b.bits[0], dec2 = b.bits[1], dec3 = b.bits[2], dec4 = b.bits[3];

  printf("\nprint int\n");
  print_bit_int(a);
  printf("\nprint decimal\n");
  print_bit_dec(dec1, dec2, dec3, dec4);

  return 0;
}
