#include <stdio.h>

// This function takes a double pointer (pointer to a pointer)
// so that it can modify the original pointer in main.
void switch_score(int **current_score, int *new_score) {
    // Dereferencing once (*current_score) lets us change 
    // where the original pointer is pointing.
    *current_score = new_score;
}

int main() {
    int first_score = 10;
    int bonus_score = 25;
    
    // selected_score starts out pointing to first_score
    int *selected_score = &first_score;

    printf("before\n");
    printf("%d\n", *selected_score);

    // We pass the ADDRESS of the pointer (&selected_score)
    // and the address of the new score.
    switch_score(&selected_score, &bonus_score);

    printf("after\n");
    // Now selected_score points to bonus_score!
    printf("%d\n", *selected_score);

    return 0;
}