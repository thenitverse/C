
#include <stdio.h>
#include <stdlib.h>

int *allocate_scalar_array(int size, int multiplier) {
  int *ptr = malloc(size * sizeof(int));
  if (ptr == NULL) {
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    ptr[i] = i * multiplier;
  }
  return ptr;
}



int main() {
  int size = 5;
  int multiplier = 2;

  int *arr = allocate_scalar_array(size, multiplier);
  if (arr == NULL) {
    printf("Allocation failed\n");
    return 1;
  }

  for (int i = 0; i < size; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }

  free(arr); //Since the array was allocated on the heap with malloc, it won't be automatically cleaned up. You must manually release it with free"""
  return 0;
}
