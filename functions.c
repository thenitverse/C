#include <stdio.h>
float get_average(int x,int y, int z){
    return (x+y+z)/3.0;
}


int main() {
    printf("%f\n", get_average(3, 3, 5));
    printf("%f\n",get_average(4,5,6));
    return 0;
}