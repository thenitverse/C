#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---- Type definitions ----

typedef struct SnekObject snek_object_t;

typedef struct snek_vector {
  snek_object_t *x;
  snek_object_t *y;
  snek_object_t *z;
} snek_vector_t;

typedef enum snek_object_kind {
  INTEGER,
  FLOAT,
  STRING,
  VECTOR3,
} snek_object_kind_t;

typedef union snek_object_data {
  int v_int;
  float v_float;
  char *v_string;
  snek_vector_t v_vector3;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;
// ---- Constructors ----

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

  size_t len = strlen(value);
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

// ---- Tests ----

void test_null_guards(void) {
  assert(new_snek_vector3(NULL, NULL, NULL) == NULL);

  snek_object_t *x = new_snek_integer(5);
  assert(new_snek_vector3(x, NULL, NULL) == NULL);

  snek_object_t *y = new_snek_integer(6);
  assert(new_snek_vector3(x, y, NULL) == NULL);

  free(x);
  free(y);
  printf("test_null_guards passed\n");
}

void test_distinct_objects(void) {
  snek_object_t *x = new_snek_integer(1);
  snek_object_t *y = new_snek_integer(2);
  snek_object_t *z = new_snek_integer(3);
  snek_object_t *vec = new_snek_vector3(x, y, z);

  assert(vec != NULL);
  assert(vec->kind == VECTOR3);
  assert(vec->data.v_vector3.x == x);
  assert(vec->data.v_vector3.y == y);
  assert(vec->data.v_vector3.z == z);
  assert(vec->data.v_vector3.x->data.v_int == 1);
  assert(vec->data.v_vector3.z->data.v_int == 3);

  free(x);
  free(y);
  free(z);
  free(vec);
  printf("test_distinct_objects passed\n");
}

void test_same_object(void) {
  snek_object_t *i = new_snek_integer(1);
  snek_object_t *vec = new_snek_vector3(i, i, i);

  assert(vec->data.v_vector3.x == i);
  i->data.v_int = 99;
  assert(vec->data.v_vector3.y->data.v_int == 99);
  assert(vec->data.v_vector3.z->data.v_int == 99);

  free(i);
  free(vec);
  printf("test_same_object passed\n");
}

void test_mixed_kinds(void) {
  snek_object_t *f = new_snek_float(1.5f);
  snek_object_t *s = new_snek_string("hi");
  snek_object_t *n = new_snek_integer(7);
  snek_object_t *vec = new_snek_vector3(f, s, n);

  assert(vec->data.v_vector3.y->kind == STRING);

  free(s->data.v_string); // string buffer was malloc'd separately
  free(f);
  free(s);
  free(n);
  free(vec);
  printf("test_mixed_kinds passed\n");
}

int main(void) {
  test_null_guards();
  test_distinct_objects();
  test_same_object();
  test_mixed_kinds();
  printf("All tests passed\n");
  return 0;
}