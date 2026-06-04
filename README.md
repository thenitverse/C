## Mark & Sweep Garbage Collector (C)

A simple **mark-and-sweep garbage collector** built in C .

This project implements a tiny virtual machine ("VM") that tracks objects,
groups them into stack frames, and automatically frees memory that is no
longer reachable.


## What I learned

- Using `malloc`, `calloc`, and `free` to manage memory myself
- The stack vs the heap, and why it matters
- How pointers work (and how easy it is to mess them up)
- Memory leaks and dangling pointers, and how to avoid them
- Building data structures like a dynamic stack from scratch
- How a garbage collector works by building a mark-and-sweep one:
  - **Mark** the objects still being used
  - **Trace** through their references to find everything reachable
  - **Sweep** away whatever's left to free the memory

## Hardest part

Pointers and stack allocation were the toughest for me. Wrapping my head
around what a pointer actually points to, and how the stack stores things,
took a while to click. But once it did, the rest made way more sense


## Notes
This was a learning project. Taught me a lot about how memory works under
the hood in C (malloc/free, dangling pointers, and why GC exists).


