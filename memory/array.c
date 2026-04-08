#include <stdio.h>
void update_file(int filedata[200],int new_filetype,int new_num_lines){
    filedata[1] = new_num_lines;
    filedata[2] = new_filetype;
    filedata[199] = 0;
}
int main(){
    int filedata[200] = {0};
    for(int i = 0;i < 200;i++){
        filedata[1] = 99;

    }
    update_file(filedata, 3, 250);

    printf("Index 1 (num_lines): %d\n", filedata[1]);
    printf("Index 2 (filetype):  %d\n", filedata[2]);
    printf("Index 199 (end):     %d\n", filedata[199]);

    return 0;
}
