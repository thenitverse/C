#include <stdio.h>
float sneak_score(int num_files,int num_contributors,int num_commits,float avg_bug){
    int size_factor = num_files*num_commits;
    int complexity_factor = num_contributors+size_factor;
    float final_result = complexity_factor*avg_bug;
    return final_result;
}

    int main() {
    float score = sneak_score(3, 4, 5, 0.1);
    printf("score: %f\n", score);
}