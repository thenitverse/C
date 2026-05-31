#include "snek.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void refcount_inc(snek_object_t *obj){
    if (obj == NULL){
        return;
    }
    obj->refcount +=1;
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

void test_initial_refcount() {
    snek_object_t *obj = new_snek_integer(42);
    assert(obj != NULL);
    assert(obj->refcount == 1);
    free(obj);
    printf("PASS: test_initial_refcount\n");
}

void test_inc_once() {
    snek_object_t *obj = new_snek_integer(10);
    refcount_inc(obj);
    assert(obj->refcount == 2);
    free(obj);
    printf("PASS: test_inc_once\n");
}

void test_inc_multiple() {
    snek_object_t *obj = new_snek_float(3.14f);
    refcount_inc(obj);
    refcount_inc(obj);
    refcount_inc(obj);
    assert(obj->refcount == 4);
    free(obj);
    printf("PASS: test_inc_multiple\n");
}

void test_null_does_not_crash() {
    // Should do nothing, not segfault
    refcount_inc(NULL);
    printf("PASS: test_null_does_not_crash\n");
}

void test_string_refcount() {
    snek_object_t *obj = new_snek_string("hello");
    assert(obj->refcount == 1);
    refcount_inc(obj);
    assert(obj->refcount == 2);
    free(obj->data.v_string);
    free(obj);
    printf("PASS: test_string_refcount\n");
}

void test_array_refcount() {
    snek_object_t *obj = new_snek_array(5);
    assert(obj->refcount == 1);
    refcount_inc(obj);
    assert(obj->refcount == 2);
    free(obj->data.v_array.elements);
    free(obj);
    printf("PASS: test_array_refcount\n");
}

int main() {
    test_initial_refcount();
    test_inc_once();
    test_inc_multiple();
    test_null_does_not_crash();
    test_string_refcount();
    test_array_refcount();
    printf("\nAll tests passed.\n");
    return 0;
}
/*output:
PASS: test_initial_refcount
PASS: test_inc_once
PASS: test_inc_multiple
PASS: test_null_does_not_crash
PASS: test_string_refcount
PASS: test_array_refcount

All tests passed.*/