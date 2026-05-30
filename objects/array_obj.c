#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>




typedef struct SnekObject snek_object_t;
typedef struct snek_array{
  size_t size;
  snek_object_t **elements;
}snek_array_t;


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

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *ptr = malloc(sizeof(snek_object_t));
  if (ptr == NULL){
    return NULL;
  }
  snek_object_t **p = calloc(size,sizeof(snek_object_t *));
  if (p == NULL){
    free(ptr);
    return NULL;
  }
  ptr->kind = ARRAY;
  ptr->data.v_array = (snek_array_t){.size = size,.elements = p};
  return ptr;
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


int main() {
  snek_object_t *arr = new_snek_array(3);

  assert(arr != NULL);
  assert(arr->kind == ARRAY);
  assert(arr->data.v_array.size == 3);

  assert(arr->data.v_array.elements != NULL);
  assert(arr->data.v_array.elements[0] == NULL);
  assert(arr->data.v_array.elements[1] == NULL);
  assert(arr->data.v_array.elements[2] == NULL);

  free(arr->data.v_array.elements);
  free(arr);

  printf("array test passed\n");
  return 0;
}