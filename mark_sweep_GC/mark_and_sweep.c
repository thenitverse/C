#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// A simple "object" with a mark bit and a pointer to another object
typedef struct Object {
    bool is_marked;
    struct Object *next; // simulates a reference to another object
} Object;

// --- MARK PHASE ---
// Recursively mark an object and anything it references
void mark(Object *obj) {
    if (obj == NULL || obj->is_marked) return;
    obj->is_marked = true;
    mark(obj->next); // follow references
}

// --- SWEEP PHASE ---
// Walk the heap, free unmarked objects, reset marks on survivors
void sweep(Object **heap, int count) {
    for (int i = 0; i < count; i++) {
        if (heap[i] == NULL) continue;
        if (!heap[i]->is_marked) {
            printf("Sweeping object %d\n", i);
            free(heap[i]);
            heap[i] = NULL;
        } else {
            heap[i]->is_marked = false; // reset for next GC cycle
        }
    }
}

int main() {
    // Simulate a small "heap" of 4 objects
    Object *heap[4];
    for (int i = 0; i < 4; i++) {
        heap[i] = calloc(1, sizeof(Object));
    }

    // heap[0] -> heap[1] (reachable chain)
    heap[0]->next = heap[1];
    // heap[2] and heap[3] are unreachable (no references to them)

    // Mark from a "root" (heap[0] is our root)
    mark(heap[0]);

    // Sweep: collect anything not marked
    sweep(heap, 4);

    // heap[0] and heap[1] survive; heap[2] and heap[3] are freed
    printf("heap[0] alive: %s\n", heap[0] != NULL ? "yes" : "no");
    printf("heap[1] alive: %s\n", heap[1] != NULL ? "yes" : "no");
    printf("heap[2] alive: %s\n", heap[2] != NULL ? "yes" : "no");
    printf("heap[3] alive: %s\n", heap[3] != NULL ? "yes" : "no");

    // Clean up survivors
    free(heap[0]);
    free(heap[1]);
    return 0;
}
/*output:
sweeping object 2
Sweeping object 3
heap[0] alive: yes
heap[1] alive: yes
heap[2] alive: no
heap[3] alive: no*/