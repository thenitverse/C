#include "snek.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

snek_object_t *new_snek_object(){
    snek_object_t *ptr = calloc(1,sizeof(snek_object_t));  //calloc(count,size): count = 1 not 0 because count starts here from 1 for assiging room to value.
    if (ptr == NULL){
        return NULL;
    }
    ptr->refcount = 1;
    return ptr;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = new_snek_object();
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

  snek_object_t *obj = new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;
  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;
  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = new_snek_object();
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
    // Test integer
    snek_object_t *i = new_snek_integer(42);
    assert(i != NULL);
    assert(i->refcount == 1);
    assert(i->kind == INTEGER);
    assert(i->data.v_int == 42);
    free(i);
    printf("integer: OK\n");

    // Test float
    snek_object_t *f = new_snek_float(3.14f);
    assert(f != NULL);
    assert(f->refcount == 1);
    assert(f->kind == FLOAT);
    free(f);
    printf("float: OK\n");

    // Test string
    snek_object_t *s = new_snek_string("hello");
    assert(s != NULL);
    assert(s->refcount == 1);
    assert(s->kind == STRING);
    assert(s->data.v_string[0] == 'h');
    free(s->data.v_string);
    free(s);
    printf("string: OK\n");

    // Test array
    snek_object_t *a = new_snek_array(3);
    assert(a != NULL);
    assert(a->refcount == 1);
    assert(a->kind == ARRAY);
    assert(a->data.v_array.size == 3);
    free(a->data.v_array.elements);
    free(a);
    printf("array: OK\n");

    printf("All tests passed!\n");
    return 0;
}
/*output:
integer: OK
float: OK
string: OK
array: OK
All tests passed!
*/