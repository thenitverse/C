#include <stdlib.h>
#include <assert.h>
#include <math.h>

typedef enum snek_object_kind{
    INTEGER,
    FLOAT
}snek_object_kind_t;
typedef union  snek_object_data
{
    int v_int;
    float v_float;
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
    snek_object_t *ptr = malloc(sizeof(snek_object_t));
    if (ptr == NULL){
        return NULL;
    }
    ptr->kind = FLOAT;
    ptr->data.v_float = value;
    return ptr;
}

void test_new_snek_int() {
    snek_object_t *obj = new_snek_int(42);

    assert(obj != NULL);
    assert(obj->kind == INTEGER);
    assert(obj->data.v_int == 42);

    free(obj);
}

void test_new_snek_float() {
    snek_object_t *obj = new_snek_float(3.14f);

    assert(obj != NULL);
    assert(obj->kind == FLOAT);
    assert(fabs(obj->data.v_float - 3.14f) < 0.001f);

    free(obj);
}

int main() {
    test_new_snek_int();
    test_new_snek_float();

    return 0;
}