#include <stdio.h>
#include "limits.h"

typedef union 
{
    int value;
    unsigned int err;

    
}val_or_err_t;

int main(){
    val_or_err_t lane_scores = {.value = -20};
    printf("value (set): %d\n",lane_scores.value);
    printf("err (unset): %u\n", lane_scores.err);

    val_or_err_t teejs_score = {.err = UINT_MAX};
    printf("value (unset): %d\n", teejs_score.value);
    printf("err (set): %u\n", teejs_score.err);
}

