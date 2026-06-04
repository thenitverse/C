#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A simple "object" with a mark flag
typedef struct {
  int value;
  bool is_marked;
} obj_t;

// A simple "frame" holding an array of object pointers
typedef struct {
  obj_t **refs;
  int ref_count;
} frame_t;

// A simple "vm" holding an array of frames
typedef struct {
  frame_t **frames;
  int frame_count;
} vm_t;

// The mark function — same pattern as the lesson
void mark(vm_t *vm) {
  for (int i = 0; i < vm->frame_count; i++) {
    frame_t *frame = vm->frames[i];
    for (int j = 0; j < frame->ref_count; j++) {
      frame->refs[j]->is_marked = true;
    }
  }
}

int main() {
  // Create two objects
  obj_t a = {.value = 1, .is_marked = false};
  obj_t b = {.value = 2, .is_marked = false};

  // Create a frame referencing both
  obj_t *refs[] = {&a, &b};
  frame_t frame = {.refs = refs, .ref_count = 2};

  // Create a vm with one frame
  frame_t *frames[] = {&frame};
  vm_t vm = {.frames = frames, .frame_count = 1};

  printf("Before mark: a=%d, b=%d\n", a.is_marked, b.is_marked);
  mark(&vm);
  printf("After mark:  a=%d, b=%d\n", a.is_marked, b.is_marked);

  return 0;
}
/*output:
Before mark: a=0, b=0
After mark:  a=1, b=1*/