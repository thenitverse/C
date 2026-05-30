#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct SnekObject snek_object_t;
snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z);
snek_object_t *new_snek_array(size_t size);
bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value);
snek_object_t *snek_array_get(snek_object_t *array, size_t index);
int snek_length(snek_object_t *obj);

int snek_length(snek_object_t *obj);
snek_object_t *snek_add(snek_object_t *a, snek_object_t *b);

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


snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a== NULL ||b == NULL){
    return NULL;
  }
  switch (a->kind){    //case int
    case INTEGER:
      switch (b->kind){
        case INTEGER:
    return new_snek_integer(a->data.v_int + b->data.v_int);
      case FLOAT:
      return new_snek_float(a->data.v_int + b->data.v_float);
        default:
        return NULL;
  }
  

    case FLOAT:    //case float
    switch (b->kind){
      case INTEGER:
        return new_snek_float(a->data.v_float + b->data.v_int);
      case FLOAT:
      return new_snek_float(a->data.v_float + b->data.v_float);
    
      default: 
        return NULL;
    }
  
    case STRING:{
    if (b->kind != STRING){  //case str
      return NULL;
    }
      int a_len = strlen(a->data.v_string);
      int b_len = strlen(b->data.v_string);
      int new_len = a_len +b_len + 1;
      char *dst = calloc(new_len,sizeof(char));
      strcat(dst,a->data.v_string);
      strcat(dst,b->data.v_string);
      snek_object_t *obj = new_snek_string(dst);
      free(dst);
      return obj;
    }
  
  case VECTOR3:{   //case vector
    if (b->kind != VECTOR3){
      return NULL;
    }
          return new_snek_vector3(
        snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
        snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
        snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
      );
    
  }
    case ARRAY: {   //case array
      if (b->kind != ARRAY){
        return NULL;
      }
      int a_len = snek_length(a);
      int b_len = snek_length(b);
      snek_object_t *result = new_snek_array(a_len + b_len);

      for (int i = 0; i < a_len; i++) {
        snek_array_set(result, i, snek_array_get(a, i));
      }
      for (int i = 0; i < b_len; i++) {
        snek_array_set(result, i + a_len, snek_array_get(b, i));
      }
    
      return result;
    }
    return NULL;
}
}


int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOAT:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case VECTOR3:
    return 3;
  case ARRAY:
    return obj->data.v_array.size;
  default:
    return -1;
  }
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

void test_integer_add() {
    snek_object_t *a = new_snek_integer(3);
    snek_object_t *b = new_snek_integer(7);
    snek_object_t *result = snek_add(a, b);

    printf("test_integer_add: ");
    if (result && result->kind == INTEGER && result->data.v_int == 10)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(a); free(b); free(result);
}

void test_int_plus_float() {
    snek_object_t *a = new_snek_integer(2);
    snek_object_t *b = new_snek_float(3.5f);
    snek_object_t *result = snek_add(a, b);

    printf("test_int_plus_float: ");
    if (result && result->kind == FLOAT && result->data.v_float == 5.5f)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(a); free(b); free(result);
}

void test_string_add() {
    snek_object_t *a = new_snek_string("hello, ");
    snek_object_t *b = new_snek_string("world");
    snek_object_t *result = snek_add(a, b);

    printf("test_string_add: ");
    if (result && result->kind == STRING &&
        strcmp(result->data.v_string, "hello, world") == 0)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(a->data.v_string); free(a);
    free(b->data.v_string); free(b);
    free(result->data.v_string); free(result);
}

void test_null_input() {
    snek_object_t *a = new_snek_integer(1);
    snek_object_t *result = snek_add(a, NULL);

    printf("test_null_input: ");
    if (result == NULL)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(a);
}

void test_type_mismatch() {
    snek_object_t *a = new_snek_integer(1);
    snek_object_t *b = new_snek_string("oops");
    snek_object_t *result = snek_add(a, b);

    printf("test_type_mismatch: ");
    if (result == NULL)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(a);
    free(b->data.v_string); free(b);
}

void test_array_add() {
    snek_object_t *one = new_snek_integer(1);
    snek_object_t *two = new_snek_integer(2);

    snek_object_t *arr_a = new_snek_array(1);
    snek_array_set(arr_a, 0, one);

    snek_object_t *arr_b = new_snek_array(1);
    snek_array_set(arr_b, 0, two);

    snek_object_t *result = snek_add(arr_a, arr_b);

    printf("test_array_add: ");
    if (result && result->kind == ARRAY && result->data.v_array.size == 2 &&
        snek_array_get(result, 0)->data.v_int == 1 &&
        snek_array_get(result, 1)->data.v_int == 2)
        printf("PASS\n");
    else
        printf("FAIL\n");

    free(one); free(two);
    free(arr_a->data.v_array.elements); free(arr_a);
    free(arr_b->data.v_array.elements); free(arr_b);
    free(result->data.v_array.elements); free(result);
}

int main() {
    test_integer_add();
    test_int_plus_float();
    test_string_add();
    test_null_input();
    test_type_mismatch();
    test_array_add();
    return 0;
}