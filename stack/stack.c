#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>   //assert takes one expression and declares true or fslse
typedef struct Stack
{
    size_t count;
    size_t capacity;
    void **data;
} sneak_stack_t;

sneak_stack_t *stack_new(size_t capacity){
    sneak_stack_t *ptr = malloc(sizeof(ptr));
    if (ptr == NULL){
        return NULL;
    }
    ptr->count = 0;  // because stack is empty
    ptr->capacity = capacity; //capacity is what we asked for 
    ptr->data = malloc(capacity * sizeof(void *));
    if (ptr->data == NULL){
        free(ptr);
        return NULL;

    }
    return ptr;
}
  

int main(void){
    sneak_stack_t *s = stack_new(3);
    assert(s != NULL);
    assert(s->count == 0);
    assert(s->capacity == 3);
    assert(s->data != NULL);
    printf("Test 1 passed: small stack created\n");
    free(s->data);
    free(s);
    return 0;
}