#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct Stack{
    size_t count;
    size_t capacity;
    void **data;
} sneak_stack_t;


void stack_push(sneak_stack_t *stack,void *obj){
    if (stack->count == stack->capacity){
        stack->capacity = 2*stack->capacity;
        void **store = realloc(stack->data,stack->capacity*sizeof(void*));
        if (store == NULL){
            stack->capacity = stack->capacity/2;
            return;
        }
        else{stack->data = store;}

    }
    stack->data[stack->count] = obj;
    stack->count = stack->count+1;
}

sneak_stack_t *stack_new(size_t capacity) {
  sneak_stack_t *ptr = malloc(sizeof(sneak_stack_t));
  if (ptr == NULL) {
    return NULL;
  }

  ptr->count = 0;
  ptr->capacity = capacity;
  ptr->data = malloc(ptr->capacity * sizeof(void *));
  if (ptr->data == NULL) {
    free(ptr);
    return NULL;
  }

  return ptr;
}




int main(void) {
    // ---- Test 1: Create a stack ----
    printf("Test 1: stack_new\n");
    sneak_stack_t *s = stack_new(2);
    assert(s != NULL);
    assert(s->count == 0);
    assert(s->capacity == 2);
    assert(s->data != NULL);
    printf("  passed\n");

    // ---- Test 2: Push without resizing ----
    printf("Test 2: push without resize\n");
    int a = 10, b = 20;
    stack_push(s, &a);
    stack_push(s, &b);
    assert(s->count == 2);
    assert(s->capacity == 2);
    assert(s->data[0] == &a);
    assert(s->data[1] == &b);
    assert(*(int *)s->data[0] == 10);
    assert(*(int *)s->data[1] == 20);
    printf("  passed\n");

    // ---- Test 3: Push triggers resize ----
    printf("Test 3: push triggers resize\n");
    int c = 30;
    stack_push(s, &c);
    assert(s->count == 3);
    assert(s->capacity == 4);          // doubled
    assert(*(int *)s->data[2] == 30);
    // old values must survive the realloc
    assert(*(int *)s->data[0] == 10);
    assert(*(int *)s->data[1] == 20);
    printf("  passed\n");

    // ---- Test 4: Multiple resizes ----
    printf("Test 4: multiple resizes\n");
    int d = 40, e = 50, f = 60;
    stack_push(s, &d);   // count=4, capacity=4
    stack_push(s, &e);   // triggers resize → capacity=8, count=5
    stack_push(s, &f);   // count=6, capacity=8
    assert(s->count == 6);
    assert(s->capacity == 8);
    assert(*(int *)s->data[5] == 60);
    printf("  passed\n");

    // ---- Test 5: Push different types (void* is generic) ----
    printf("Test 5: heterogeneous types\n");
    sneak_stack_t *s2 = stack_new(2);
    int   num   = 99;
    char  ch    = 'Z';
    char *str   = "hello";
    stack_push(s2, &num);
    stack_push(s2, &ch);
    stack_push(s2, str);     // already a pointer
    assert(s2->count == 3);
    assert(*(int *)s2->data[0] == 99);
    assert(*(char *)s2->data[1] == 'Z');
    assert(strcmp((char *)s2->data[2], "hello") == 0);
    printf("  passed\n");

    // ---- Cleanup ----
    free(s->data);
    free(s);
    free(s2->data);
    free(s2);

    printf("\nAll tests passed!\n");
    return 0;
}
