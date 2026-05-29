#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



typedef enum snek_object_kind{
    INTEGER
    
}snek_object_kind_t;

typedef union snek_object_data
{
    int v_int;
}snek_object_data_t;

typedef struct snek_object{
    snek_object_kind_t kind;
    snek_object_data_t data;
}snek_object_t;


int main(void) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));

  obj->kind = INTEGER;
  obj->data.v_int = 42;

  assert(obj->kind == INTEGER);
  assert(obj->data.v_int == 42);

  free(obj);

  return 0;
  


}