#include <stdio.h>

typedef struct codefile {
    int lines;
    int filetype;

} codefile_t;
codefile_t change_filetype(codefile_t *f, int new_filetype) {
    codefile_t new_f = *f;
    new_f.filetype = new_filetype;
    return new_f;
}

int main() {
    codefile_t original;
    original.lines = 100;
    original.filetype = 1;

    codefile_t result = change_filetype(&original, 2);

    printf("New filetype: %d\n", result.filetype);   // expect 2
    printf("Lines unchanged: %d\n", result.lines);   // expect 100
    printf("Original unchanged: %d\n", original.filetype); // expect 1

    return 0;
}