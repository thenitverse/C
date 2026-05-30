#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SnekObject snek_object_t;
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


snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
  if (snek_obj == NULL){
  return NULL;
  }
  if (snek_obj->kind != ARRAY){
    return NULL;
  }
  if (snek_obj->data.v_array.size <= index){
    return NULL;
    
  
}
   return snek_obj->data.v_array.elements[index];
}

bool snek_array_set(snek_object_t *snek_obj, size_t index,
                    snek_object_t *value) {
  if (snek_obj == NULL || value == NULL) {
    return false;
  }

  if (snek_obj->kind != ARRAY) {
    return false;
  }

  if (index >= snek_obj->data.v_array.size) {
    return false;
  }

  snek_obj->data.v_array.elements[index] = value;
  return true;
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

void test_null_input() {
    assert(snek_array_get(NULL, 0) == NULL);
    printf("test_null_input passed\n");
}

void test_non_array_input() {
    snek_object_t *obj = new_snek_integer(5);
    assert(snek_array_get(obj, 0) == NULL);
    free(obj);
    printf("test_non_array_input passed\n");
}

void test_out_of_bounds() {
    snek_object_t *arr = new_snek_array(3);
    assert(snek_array_get(arr, 3) == NULL);
    assert(snek_array_get(arr, 99) == NULL);
    free(arr->data.v_array.elements);
    free(arr);
    printf("test_out_of_bounds passed\n");
}

void test_empty_slot() {
    snek_object_t *arr = new_snek_array(3);
    assert(snek_array_get(arr, 0) == NULL);
    assert(snek_array_get(arr, 2) == NULL);
    free(arr->data.v_array.elements);
    free(arr);
    printf("test_empty_slot passed\n");
}

void test_happy_path() {
    snek_object_t *arr = new_snek_array(2);
    snek_object_t *item = new_snek_integer(42);
    snek_array_set(arr, 0, item);

    assert(snek_array_get(arr, 0) == item);
    assert(snek_array_get(arr, 1) == NULL);

    free(item);
    free(arr->data.v_array.elements);
    free(arr);
    printf("test_happy_path passed\n");
}

void test_string_item() {
    snek_object_t *arr = new_snek_array(1);
    snek_object_t *item = new_snek_string("hello");
    snek_array_set(arr, 0, item);

    snek_object_t *result = snek_array_get(arr, 0);
    assert(result == item);
    assert(result->kind == STRING);

    free(item->data.v_string);
    free(item);
    free(arr->data.v_array.elements);
    free(arr);
    printf("test_string_item passed\n");
}

int main() {
    test_null_input();
    test_non_array_input();
    test_out_of_bounds();
    test_empty_slot();
    test_happy_path();
    test_string_item();
    printf("All tests passed!\n");
    return 0;
}