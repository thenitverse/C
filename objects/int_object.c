#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


typedef enum snek_object_kind{
    INTEGER
}snek_object_kind_t;
typedef union snek_object_data
{
    int v_int;
}snek_object_data_t;
typedef struct snek_object{
    snek_object_kind_t kind;
    snek_object_data_t data;
}snek_object_t;
snek_object_t *new_snek_integer(int value){
    snek_object_t *ptr = malloc(sizeof(snek_object_t));
    if (ptr == NULL){
        return NULL;

    }
    ptr->kind = INTEGER;
    ptr->data.v_int = value;
    return ptr;
}


int main() {
  // Test 1: positive number
  snek_object_t *a = new_snek_integer(42);
  assert(a != NULL);
  assert(a->kind == INTEGER);
  assert(a->data.v_int == 42);
  printf("Test 1 passed: positive\n");
  free(a);

  // Test 2: zero
  snek_object_t *b = new_snek_integer(0);
  assert(b != NULL);
  assert(b->data.v_int == 0);
  printf("Test 2 passed: zero\n");
  free(b);

  // Test 3: negative number
  snek_object_t *c = new_snek_integer(-5);
  assert(c != NULL);
  assert(c->kind == INTEGER);
  assert(c->data.v_int == -5);
  printf("Test 3 passed: negative\n");
  free(c);

  printf("All tests passed!\n");
  return 0;
}

/*output:
Test 1 passed: positive
Test 2 passed: zero
Test 3 passed: negative
All tests passed!*/