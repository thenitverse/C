#include "snek.h"
                      //Object is created (refcount = 1)
#include "assert.h"   //Something else grabs a reference to it -- refcount_inc (refcount = 2)
#include <stdio.h>    //That something else is done -- refcount_dec (refcount = 1)
#include <stdlib.h>   //The original owner is done -- refcount_dec (refcount = 0) -- memory freed
#include <string.h>
void refcount_free(snek_object_t *obj);
void refcount_dec(snek_object_t *obj){
    if (obj == NULL){
        return;
    }
    obj->refcount -=1;
    if (obj->refcount == 0){
        refcount_free(obj);
    }
}
void refcount_free(snek_object_t *obj) {
  switch (obj->kind){
    case INTEGER:
    case FLOAT:
    break;
    case STRING:
    free(obj->data.v_string);
    break;
    default:
    return;
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


// ---- Tests ----

void test_initial_refcount() {
  snek_object_t *obj = new_snek_integer(42);
  assert(obj->refcount == 1);
  free(obj);
  printf("PASS: test_initial_refcount\n");
}

void test_refcount_inc() {
  snek_object_t *obj = new_snek_float(3.14f);
  refcount_inc(obj);
  assert(obj->refcount == 2);
  free(obj);
  printf("PASS: test_refcount_inc\n");
}

void test_refcount_dec_no_free() {
  snek_object_t *obj = new_snek_integer(10);
  refcount_inc(obj);           // refcount = 2
  refcount_dec(obj);           // refcount = 1, should NOT free
  assert(obj->refcount == 1);
  free(obj);                   // manual cleanup
  printf("PASS: test_refcount_dec_no_free\n");
}

void test_null_inc_dec() {
  // Neither should crash on NULL
  refcount_inc(NULL);
  refcount_dec(NULL);
  printf("PASS: test_null_inc_dec\n");
}

void test_integer_freed_at_zero() {
  snek_object_t *obj = new_snek_integer(99);
  // refcount starts at 1, decrement to 0 triggers refcount_free
  // If this doesn't crash or leak under valgrind, it's correct
  refcount_dec(obj);
  printf("PASS: test_integer_freed_at_zero\n");
}

void test_float_freed_at_zero() {
  snek_object_t *obj = new_snek_float(2.71f);
  refcount_dec(obj);
  printf("PASS: test_float_freed_at_zero\n");
}

void test_string_freed_at_zero() {
  snek_object_t *obj = new_snek_string("hello world");
  assert(strcmp(obj->data.v_string, "hello world") == 0);
  // Decrement to 0: should free both the string buffer and the object
  refcount_dec(obj);
  printf("PASS: test_string_freed_at_zero\n");
}

void test_string_survives_one_dec() {
  snek_object_t *obj = new_snek_string("still alive");
  refcount_inc(obj);                                      // refcount = 2
  refcount_dec(obj);                                      // refcount = 1
  assert(strcmp(obj->data.v_string, "still alive") == 0);
  refcount_dec(obj);                                      // refcount = 0, freed
  printf("PASS: test_string_survives_one_dec\n");
}

int main() {
  test_initial_refcount();
  test_refcount_inc();
  test_refcount_dec_no_free();
  test_null_inc_dec();
  test_integer_freed_at_zero();
  test_float_freed_at_zero();
  test_string_freed_at_zero();
  test_string_survives_one_dec();

  printf("\nAll tests passed.\n");
  return 0;
}
/*output:
PASS: test_initial_refcount
PASS: test_refcount_inc
PASS: test_refcount_dec_no_free
PASS: test_null_inc_dec
PASS: test_integer_freed_at_zero
PASS: test_float_freed_at_zero
PASS: test_string_freed_at_zero
PASS: test_string_survives_one_dec

All tests passed.*/