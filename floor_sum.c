#include <stdio.h>

int sum_special_floors(int top_floor) {
    if (top_floor <= 0) {
        return 0;
    }

    int total = 0;

    for (int i = 1; i <= top_floor; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            total += i;
        }
    }

    return total;
}

int main() {
    printf("%d\n", sum_special_floors(5));   //  3+5 = 8 ie only 3 and 5 are divisible so their sum is 8
    printf("%d\n", sum_special_floors(10));  // 33
    printf("%d\n", sum_special_floors(15));  // 60
  
    printf("%d\n", sum_special_floors(0));   // 0
    printf("%d\n", sum_special_floors(20));  // 98

    return 0;
}