#include <stdio.h>
#include <string.h>
typedef struct {
    size_t length;
    char buffer[64];
}TextBuffer;
int smart_append(TextBuffer *dest, const char *src){
    if (dest == NULL || src == NULL){
        return 1;
    }
    const int max_buffer = 64;
    size_t len = strlen(src);
    size_t remaining = max_buffer - dest->length-1;
    if (len > remaining){
        strncat(dest->buffer,src,remaining);
        dest->length = max_buffer -1;
        return 1;
    }
    else{
        strcat(dest->buffer,src);
        dest->length +=len;
        return 0;
    }
}
int main() {
    TextBuffer tb = {0, ""};

    printf("Result: %d\n", smart_append(&tb, "Hello"));
    printf("Buffer: %s\n", tb.buffer);
    printf("Length: %zu\n", tb.length);

    printf("Result: %d\n", smart_append(&tb, " World"));
    printf("Buffer: %s\n", tb.buffer);
    printf("Length: %zu\n", tb.length);

    printf("NULL test: %d\n", smart_append(NULL, "test"));

    return 0;
}