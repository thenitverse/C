#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// --- Type definitions ---

typedef struct SnekObject snek_object_t;

typedef struct {
  size_t size;
  snek_object_t **elements;
} snek_array_t;

typedef enum {
  INTEGER,
  FLOAT,
  STRING,
  ARRAY,
} snek_object_kind_t;

typedef union {
  int v_int;
  float v_float;
  char *v_string;
  snek_array_t v_array;
} snek_object_data_t;

typedef struct SnekObject {
  int refcount;
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

// --- Forward declarations ---

void refcount_inc(snek_object_t *obj);
void refcount_dec(snek_object_t *obj);
void refcount_free(snek_object_t *obj);

// --- Implementation ---

snek_object_t *_new_snek_object() {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) return NULL;
  obj->refcount = 1;
  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) return NULL;

  snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
  if (elements == NULL) {
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
  return obj;
}

void refcount_free(snek_object_t *obj) {
  if (obj->kind == ARRAY) {
    snek_array_t array = obj->data.v_array;
    for (size_t i = 0; i < array.size; i++) {
      refcount_dec(array.elements[i]);
    }
    free(array.elements);
  }
  free(obj);
}

void refcount_inc(snek_object_t *obj) {
  if (obj == NULL) return;
  obj->refcount++;
}

void refcount_dec(snek_object_t *obj) {
  if (obj == NULL) return;
  obj->refcount--;
  if (obj->refcount == 0) {
    refcount_free(obj);
  }
}

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
  if (snek_obj == NULL || value == NULL) return false;
  if (snek_obj->kind != ARRAY) return false;
  if (index >= snek_obj->data.v_array.size) return false;

  refcount_inc(value);
  if (snek_obj->data.v_array.elements[index] != NULL) {
    refcount_dec(snek_obj->data.v_array.elements[index]);
  }
  snek_obj->data.v_array.elements[index] = value;
  return true;
}

// --- Demo ---

int main() {
  snek_object_t *first = new_snek_array(1);
  snek_object_t *second = new_snek_array(1);

  // refcounts: first = 1, second = 1
  snek_array_set(first, 0, second);
  // refcounts: first = 1, second = 2
  snek_array_set(second, 0, first);
  // refcounts: first = 2, second = 2

  refcount_dec(first);
  refcount_dec(second);
  // Cycle: both stuck at 1, neither freed

  printf("first->refcount = %d (expected 1)\n", first->refcount);
  printf("second->refcount = %d (expected 1)\n", second->refcount);

  assert(first->refcount == 1);
  assert(second->refcount == 1);

  printf("PASS: Demonstrated reference counting cycle bug.\n");
  printf("NOTE: Memory leak is expected here — this is the known limitation.\n");

  return 0;
}
/**output:
first->refcount = 1 (expected 1)
second->refcount = 1 (expected 1)
PASS: Demonstrated reference counting cycle bug.
NOTE: Memory leak is expected here xe2x80x94 this is the known limitation*/