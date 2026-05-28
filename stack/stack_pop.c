#include <stddef.h>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} s_stack_t;




void *stack_pop(s_stack_t *stack) {
  if (stack->count == 0){
    return NULL;
  }
 
  stack->count--;
  return stack->data[stack->count];
}
void stack_push(s_stack_t *stack, void *obj) {
  if (stack->count == stack->capacity) {
    stack->capacity *= 2;
    void **temp = realloc(stack->data, stack->capacity * sizeof(void *));
    if (temp == NULL) {
      stack->capacity /= 2;

      exit(1);
    }
    stack->data = temp;
  }
  stack->data[stack->count] = obj;
  stack->count++;
  return;
}

s_stack_t *stack_new(size_t capacity) {
  s_stack_t *stack = malloc(sizeof(s_stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(stack->capacity * sizeof(void *));
  if (stack->data == NULL) {
    free(stack);
    return NULL;
  }

  return stack;
}


int main(void) {
    // Test 1: pop from empty stack returns NULL
    s_stack_t *s = stack_new(2);
    if (stack_pop(s) == NULL) {
        printf("Test 1 passed: empty pop returns NULL\n");
    }

    // Test 2: push and pop a single element
    int a = 42;
    stack_push(s, &a);
    int *out = stack_pop(s);
    if (out != NULL && *out == 42) {
        printf("Test 2 passed: single push/pop\n");
    }

    // Test 3: LIFO order
    int x = 1, y = 2, z = 3;
    stack_push(s, &x);
    stack_push(s, &y);
    stack_push(s, &z);
    int *p1 = stack_pop(s);
    int *p2 = stack_pop(s);
    int *p3 = stack_pop(s);
    if (*p1 == 3 && *p2 == 2 && *p3 == 1) {
        printf("Test 3 passed: LIFO order preserved\n");
    }

    // Test 4: capacity doubles on overflow
    s_stack_t *s2 = stack_new(2);
    int v = 7;
    stack_push(s2, &v);
    stack_push(s2, &v);
    stack_push(s2, &v); // triggers realloc
    if (s2->capacity == 4 && s2->count == 3) {
        printf("Test 4 passed: capacity doubled\n");
    }

    // Test 5: pop after capacity grew
    int *pv = stack_pop(s2);
    if (pv != NULL && *pv == 7 && s2->count == 2) {
        printf("Test 5 passed: pop after resize\n");
    }

    // Test 6: mixed types via void* (pointers to different types)
    s_stack_t *s3 = stack_new(2);
    int i = 99;
    char c = 'Z';
    double d = 3.14;
    stack_push(s3, &i);
    stack_push(s3, &c);
    stack_push(s3, &d);
    if (*(double *)stack_pop(s3) == 3.14 &&
        *(char *)stack_pop(s3) == 'Z' &&
        *(int *)stack_pop(s3) == 99) {
        printf("Test 6 passed: heterogeneous pointers\n");
    }

    // Cleanup
    free(s->data);  free(s);
    free(s2->data); free(s2);
    free(s3->data); free(s3);
    return 0;
}