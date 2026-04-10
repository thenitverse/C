#include <stdio.h>
typedef struct graphics

{
    int fps;
    int height;
    int width;
}graphics_t;

void dump_graphics(graphics_t gsettings[10]){
    int *ptr = (int *)gsettings;
    for(int i = 0; i < 30;i++) {
        printf("settings[%d] = %d\n",i,ptr[i]);
    }
}
int main(){
    graphics_t graphics_array[10]={
        {1,2,3},{2,3,4},{5,6,7},{8,9,10},{11,12,13},{14,15,16},{17,18,19},{20,21,22},{23,24,25},{26,27,28},

    };
    dump_graphics(graphics_array);
    return 0;
}
