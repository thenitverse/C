#include <stdio.h>

void swap_ints(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void test_swap_ints() {
  int a = 5;
  int b = 6;

  swap_ints(&a, &b);

  printf("Test 1 - Basic swap:\n");
  printf("  a = %d (expected 6): %s\n", a, a == 6 ? "PASS" : "FAIL");
  printf("  b = %d (expected 5): %s\n", b, b == 5 ? "PASS" : "FAIL");
}

void test_swap_same_pointer() {
  int a = 5;

  swap_ints(&a, &a);

  printf("Test 2 - Same pointer:\n");
  printf("  a = %d (expected 5): %s\n", a, a == 5 ? "PASS" : "FAIL");
}

void test_swap_negatives() {
  int a = -10;
  int b = 20;

  swap_ints(&a, &b);

  printf("Test 3 - Negative values:\n");
  printf("  a = %d (expected 20): %s\n", a, a == 20 ? "PASS" : "FAIL");
  printf("  b = %d (expected -10): %s\n", b, b == -10 ? "PASS" : "FAIL");
}

int main() {
  test_swap_ints();
  test_swap_same_pointer();
  test_swap_negatives();
  return 0;
}