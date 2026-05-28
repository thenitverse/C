
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



typedef struct Stack {
    size_t count;
    size_t capacity;
    void **data;
} s_stack_t;

s_stack_t *stack_new(size_t capacity) {
    s_stack_t *s = malloc(sizeof(s_stack_t));
    s->count = 0;
    s->capacity = capacity;
    s->data = malloc(capacity * sizeof(void *));
    return s;
}

void stack_push(s_stack_t *s, void *obj) {
    s->data[s->count] = obj;
    s->count++;
}

void stack_free(s_stack_t *s) {
    free(s->data);
    free(s);
}



void scary_double_push(s_stack_t *s) {
    stack_push(s, (void *)1337);

    int *ptr = malloc(sizeof(int));
    *ptr = 1024;
    stack_push(s, ptr);
}

// --- Simple tests ---

int main(void) {
    s_stack_t *s = stack_new(2);
    scary_double_push(s);

    // Test 1: count
    assert(s->count == 2);
    printf("Test 1 passed: count is 2\n");

    // Test 2: slot 0 is the raw int 1337 cast back
    int value = (int)s->data[0];
    assert(value == 1337);
    printf("Test 2 passed: slot 0 holds 1337\n");

    // Test 3: slot 1 is a real pointer to 1024
    int *pointer = s->data[1];
    assert(*pointer == 1024);
    printf("Test 3 passed: slot 1 points to 1024\n");

    // Cleanup — only slot 1 is a real allocation
    free(pointer);
    stack_free(s);

    printf("All tests passed!\n");
    return 0;
}