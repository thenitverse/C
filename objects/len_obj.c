#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

typedef struct SnekObject snek_object_t;

int snek_length(snek_object_t *obj);

typedef struct {
  size_t size;
  snek_object_t **elements;
} snek_array_t;

typedef struct {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef enum SnekObjectKind {
  INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
  ARRAY,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
  snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;
int snek_length(snek_object_t *obj) {
  if (obj == NULL){
    return -1;
  }
  if (obj->kind ==INTEGER){
    return 1;
  }
  if (obj->kind == FLOAT){
    return 1;
  }
  if (obj->kind == STRING){
    return strlen(obj->data.v_string);
  }
  if (obj->kind == VECTOR3){
    return 3;
  }
  if (obj->kind == ARRAY){
    return obj->data.v_array.size;
  }
  return -1;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
  if (array == NULL || value == NULL) {
    return false;
  }

  if (array->kind != ARRAY) {
    return false;
  }

  if (index >= array->data.v_array.size) {
    return false;
  }

  array->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
  if (array == NULL) {
    return NULL;
  }

  if (array->kind != ARRAY) {
    return NULL;
  }

  if (index >= array->data.v_array.size) {
    return NULL;
  }

  return array->data.v_array.elements[index];
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  int len = strlen(value);
  char *dst = malloc(len + 1);
  if (dst == NULL) {
    free(obj);
    return NULL;
  }

  strcpy(dst, value);

  obj->kind = STRING;
  obj->data.v_string = dst;
  return obj;
}
// test
void test_null_object() {
  assert(snek_length(NULL) == -1);
}

void test_integer_length() {
  snek_object_t *obj = new_snek_integer(42);
  assert(snek_length(obj) == 1);
  free(obj);
}

void test_float_length() {
  snek_object_t *obj = new_snek_float(3.14f);
  assert(snek_length(obj) == 1);
  free(obj);
}

void test_string_length() {
  snek_object_t *obj = new_snek_string("hello");
  assert(snek_length(obj) == 5);

  free(obj->data.v_string);
  free(obj);
}

void test_empty_string_length() {
  snek_object_t *obj = new_snek_string("");
  assert(snek_length(obj) == 0);

  free(obj->data.v_string);
  free(obj);
}

void test_vector3_length() {
  snek_object_t *x = new_snek_integer(1);
  snek_object_t *y = new_snek_integer(2);
  snek_object_t *z = new_snek_integer(3);

  snek_object_t *vec = new_snek_vector3(x, y, z);
  assert(snek_length(vec) == 3);

  free(x);
  free(y);
  free(z);
  free(vec);
}

void test_array_length() {
  snek_object_t *arr = new_snek_array(4);
  assert(snek_length(arr) == 4);

  free(arr->data.v_array.elements);
  free(arr);
}

void test_array_set_and_get() {
  snek_object_t *arr = new_snek_array(2);
  snek_object_t *value = new_snek_integer(99);

  assert(snek_array_set(arr, 0, value) == true);
  assert(snek_array_get(arr, 0) == value);

  free(value);
  free(arr->data.v_array.elements);
  free(arr);
}

void test_array_out_of_bounds() {
  snek_object_t *arr = new_snek_array(1);
  snek_object_t *value = new_snek_integer(99);

  assert(snek_array_set(arr, 5, value) == false);
  assert(snek_array_get(arr, 5) == NULL);

  free(value);
  free(arr->data.v_array.elements);
  free(arr);
}

int main() {
  test_null_object();
  test_integer_length();
  test_float_length();
  test_string_length();
  test_empty_string_length();
  test_vector3_length();
  test_array_length();
  test_array_set_and_get();
  test_array_out_of_bounds();

  printf("All tests passed!\n");
  return 0;
}