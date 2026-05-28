#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} s_stack_t;

void stack_free(s_stack_t *stack) {
  if (stack == NULL){
    return;
  }
  if (stack->data != NULL){
    free(stack->data);
  }
  free(stack);
}
void *stack_pop(s_stack_t *stack) {
  if (stack->count == 0) {
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
int main() {
  // Test 1: create a stack
  s_stack_t *s = stack_new(2);
  assert(s != NULL);
  assert(s->count == 0);
  assert(s->capacity == 2);
  printf("Test 1 passed\n");

  // Test 2: push one item
  int x = 42;
  stack_push(s, &x);
  assert(s->count == 1);
  printf("Test 2 passed\n");

  // Test 3: pop it back
  int *val = stack_pop(s);
  assert(*val == 42);
  assert(s->count == 0);
  printf("Test 3 passed\n");

  // Test 4: pop from empty stack
  assert(stack_pop(s) == NULL);
  printf("Test 4 passed\n");

  // Test 5: free the stack
  stack_free(s);
  printf("Test 5 passed\n");

  // Test 6: free NULL (should not crash)
  stack_free(NULL);
  printf("Test 6 passed\n");

  printf("All tests passed\n");
  return 0;
}