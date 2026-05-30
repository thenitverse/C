#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

bool snek_array_set(snek_object_t *snek_obj, size_t index,
                    snek_object_t *value) {
  if (snek_obj == NULL || value == NULL){
  return false;
  }
  if (snek_obj->kind != ARRAY){
    return false;
  }
  if (snek_obj->data.v_array.size <= index){
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

int main(void) {
  // Test 1: valid set at index 0
  snek_object_t *arr1 = new_snek_array(1);
  snek_object_t *val1 = new_snek_integer(42);

  assert(snek_array_set(arr1, 0, val1));
  assert(arr1->data.v_array.elements[0] == val1);

  free(val1);
  free(arr1->data.v_array.elements);
  free(arr1);

  // Test 2: NULL array should fail
  snek_object_t *val2 = new_snek_integer(100);

  assert(!snek_array_set(NULL, 0, val2));

  free(val2);

  // Test 3: NULL value should fail
  snek_object_t *arr3 = new_snek_array(1);

  assert(!snek_array_set(arr3, 0, NULL));

  free(arr3->data.v_array.elements);
  free(arr3);

  // Test 4: index equal to size should fail
  snek_object_t *arr4 = new_snek_array(2);
  snek_object_t *val4 = new_snek_integer(7);

  assert(!snek_array_set(arr4, 2, val4));

  free(val4);
  free(arr4->data.v_array.elements);
  free(arr4);

  // Test 5: non-array object should fail
  snek_object_t *not_arr = new_snek_integer(5);
  snek_object_t *val5 = new_snek_float(3.14);

  assert(!snek_array_set(not_arr, 0, val5));

  free(not_arr);
  free(val5);

  // Test 6: set two indexes without overwriting
  snek_object_t *arr6 = new_snek_array(2);
  snek_object_t *a = new_snek_integer(1);
  snek_object_t *b = new_snek_integer(2);

  assert(snek_array_set(arr6, 0, a));
  assert(snek_array_set(arr6, 1, b));
  assert(arr6->data.v_array.elements[0] == a);
  assert(arr6->data.v_array.elements[1] == b);

  free(a);
  free(b);
  free(arr6->data.v_array.elements);
  free(arr6);

  return 0;
}