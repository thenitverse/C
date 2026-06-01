#include <stdbool.h>
#include <stddef.h>
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  int refcount;
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value);
snek_object_t *new_snek_float(float value);
snek_object_t *new_snek_string(char *value);
snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z);
snek_object_t *new_snek_array(size_t size);

void refcount_inc(snek_object_t *obj);
void refcount_dec(snek_object_t *obj);
void refcount_free(snek_object_t *obj);

snek_object_t *_new_snek_object();

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }
  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
  refcount_inc(x);
  refcount_inc(y);
  refcount_inc(z);
  return obj;
}

void refcount_free(snek_object_t *obj) {
  switch (obj->kind) {
  case INTEGER:
  case FLOAT:
    break;
  case STRING:
    free(obj->data.v_string);
    break;
  case VECTOR3: {
    refcount_dec(obj->data.v_vector3.x);
    refcount_dec(obj->data.v_vector3.y);
    refcount_dec(obj->data.v_vector3.z);
    break;
  }
  default:
    assert(false);
  }

  free(obj);
}


void refcount_inc(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount++;
  return;
}

void refcount_dec(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }
  obj->refcount--;
  if (obj->refcount == 0) {
    return refcount_free(obj);
  }
  return;
}

snek_object_t *_new_snek_object() {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->refcount = 1;

  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
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

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = _new_snek_object();
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

void test_vector3_refcounting() {
    snek_object_t *x = new_snek_integer(1);
    snek_object_t *y = new_snek_integer(2);
    snek_object_t *z = new_snek_integer(3);

    snek_object_t *vec = new_snek_vector3(x, y, z);

    // Each component should now have refcount 2
    assert(x->refcount == 2);
    assert(y->refcount == 2);
    assert(z->refcount == 2);

    // Decrement vec, which should dec each component
    refcount_dec(vec);

    // Each component should be back to 1
    assert(x->refcount == 1);
    assert(y->refcount == 1);
    assert(z->refcount == 1);

    // Clean up
    refcount_dec(x);
    refcount_dec(y);
    refcount_dec(z);

    printf("test_vector3_refcounting passed\n");
}

int main() {
    test_vector3_refcounting();
    return 0;
}

/*output:
test_vector3_refcounting passed
*/