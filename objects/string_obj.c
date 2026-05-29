#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
typedef enum snek_object_kind{
    INTEGER,FLOAT,STRING,
}snek_object_kind_t;
typedef union snek_object_data{
    int v_int;
    float v_float;
    char *v_string;
}snek_object_data_t;
typedef struct snek_object{
    snek_object_kind_t kind;
    snek_object_data_t data;
}snek_object_t;
snek_object_t *new_snek_int(int value){
snek_object_t *obj = malloc(sizeof(snek_object_t));
if (obj == NULL){
    return NULL;
}
obj->kind = INTEGER;
obj->data.v_int = value;
return obj;
}
snek_object_t *new_snek_float(float value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL){
        return NULL;
    }
    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}
snek_object_t *new_snek_str(char *value){
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL){
        return NULL;
    }
    size_t len = strlen(value)+1;
    char *p = malloc(sizeof(char)*len);
    if (p == NULL){
        free(obj);
        return NULL;
    }
    strcpy(p, value);

    obj->kind = STRING;
    obj->data.v_string = p;
    return obj;
}

int main() {
    // Test integer object
    snek_object_t *int_obj = new_snek_int(42);
    assert(int_obj != NULL);
    assert(int_obj->kind == INTEGER);
    assert(int_obj->data.v_int == 42);
    free(int_obj);

    // Test float object
    snek_object_t *float_obj = new_snek_float(3.14f);
    assert(float_obj != NULL);
    assert(float_obj->kind == FLOAT);
    assert(float_obj->data.v_float > 3.13f && float_obj->data.v_float < 3.15f);
    free(float_obj);
  // Test string object
    char input[] = "hello";
    snek_object_t *str_obj = new_snek_str(input);
    assert(str_obj != NULL);
    assert(str_obj->kind == STRING);
    assert(strcmp(str_obj->data.v_string, input) == 0);

    // Make sure the string was copied into new memory
    assert(str_obj->data.v_string != input);

    free(str_obj->data.v_string);
    free(str_obj);

    // Test empty string
    char empty[] = "";
    snek_object_t *empty_obj = new_snek_str(empty);
    assert(empty_obj != NULL);
    assert(empty_obj->kind == STRING);
    assert(strcmp(empty_obj->data.v_string, "") == 0);
    assert(empty_obj->data.v_string != empty);

    free(empty_obj->data.v_string);
    free(empty_obj);

    printf("All tests passed!\n");
    return 0;
}