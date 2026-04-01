#include <stdio.h>
char *get_temp(int temp){
    if (temp < 70){
        return "too cold";
    }else if (temp > 90){
        return "too hot";
    } else {
        return "just fine";
    }
}
int main() {
    printf("%s\n", get_temp(50));
    printf("%s\n", get_temp(100));
    printf("%s\n", get_temp(75));
    return 0;
}
