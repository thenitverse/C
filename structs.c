#include <stdio.h>

struct coordinates
{
    int x;
    int y;
    int z;
};
int main(){
    struct coordinates c;
    
        c.x = 5;
        c.y = 6;
        c.z = 8;
    
    printf("x: %d, y: %d, z: %d\n", c.x, c.y, c.z);
  return 0;
    
}
