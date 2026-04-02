#include <stdio.h>
void print_numbers(int start,int end){
    for(int i = start;i < end+1;i++){
        printf("%d\n",i);
    }
}
int main() {
    print_numbers(1, 5);
    return 0;
}
