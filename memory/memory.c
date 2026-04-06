#include <stdio.h>

int main() {
    long long i = 42;

    printf("Size of i (the value):   %zu bytes\n", sizeof(i));
    printf("Size of &i (the address): %zu bytes\n", sizeof(&i));
    printf("The actual address of i: %p\n", (void*)&i);

    return 0;
}