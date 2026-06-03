#include "vm.h"
#include <assert.h>
#include <stdio.h>


void vm_frame_push(vm_t *vm, frame_t *frame) {
  stack_push(vm->frames,frame);
}

frame_t *vm_new_frame(vm_t *vm) {
  frame_t *v = malloc(sizeof(frame_t));
  v->references = stack_new(8);
  vm_frame_push(vm,v);
  return v;
}

void frame_free(frame_t *frame) {
  stack_free(frame->references);
  free(frame);
  
}

int main() {
  // Test 1: vm_new_frame pushes a frame onto vm->frames
  vm_t *vm = vm_new();
  frame_t *frame = vm_new_frame(vm);
  assert(vm->frames->count == 1);
  printf("PASS: frame was pushed\n");

  // Test 2: frame->references is allocated and empty
  assert(frame->references != NULL);
  assert(frame->references->count == 0);
  assert(frame->references->capacity > 0);
  assert(frame->references->data != NULL);
  printf("PASS: references stack initialized\n");

  // Test 3: cleanup runs without crashing
  vm_free(vm);
  printf("PASS: vm freed\n");

  printf("All tests passed!\n");
  return 0;
}