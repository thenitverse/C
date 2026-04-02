#include <stdio.h>
void print_reverse_numbers(int start,int end){
    do{
        printf("%d\n",start);
        start--;
    }while (start>=end);
    
}
int main(){
    print_reverse_numbers(20,5);
    return 0;
}