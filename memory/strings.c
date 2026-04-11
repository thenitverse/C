#include <stdio.h>
void cocat_strings(char *str1,const char *str2){
    char *end = str1;
    while(*end){
        end++;
    }
    while(*str2){
        *end = *str2;
        end++;
        str2++;
    }
    *end = '\0';
}

int main(){
    char str1[100] = "Hello ";
    const char *str2 = " world";
    cocat_strings(str1,str2);
    printf("%s\n" , str1);
    
    char str3[100] = "hy ";
    const char *str4 = " I am here.";
    cocat_strings(str3,str4);
    printf("%s\n" , str3);
    return 0;

}