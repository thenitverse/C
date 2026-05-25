#include <stdio.h>

typedef enum {
  TYPE_INT,
  TYPE_DOUBLE,
  TYPE_CHAR,
} data_type_t;

typedef struct {
  int value;
} box_int_t;

typedef struct {
  double value;
} box_double_t;

typedef struct {
  char value;
} box_char_t;

void print_value(void *ptr, data_type_t type) {
  if (type == TYPE_INT) {
    printf("int: %d\n", ((box_int_t *)ptr)->value);
  } else if (type == TYPE_DOUBLE) {
    printf("double: %f\n", ((box_double_t *)ptr)->value);
  } else if (type == TYPE_CHAR) {
    printf("char: %c\n", ((box_char_t *)ptr)->value);
  }
}

int main(void) {
  box_int_t i = {42};
  box_double_t d = {3.14};
  box_char_t c = {'Z'};

  print_value(&i, TYPE_INT);
  print_value(&d, TYPE_DOUBLE);
  print_value(&c, TYPE_CHAR);

  return 0;
}