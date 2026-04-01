#include <stdio.h>
int can_access(int is_premium ,int reputation ,int has_2fa){
    if (is_premium){
        return 1;

    }
    if (reputation >=100 && has_2fa){
        return 1;

    }
    return 0;
}
int main() {
    printf("Premium user: %d\n", can_access(1, 0, 0));        // expect 1
    printf("High rep + 2FA: %d\n", can_access(0, 100, 1));    // expect 1
    printf("High rep, no 2FA: %d\n", can_access(0, 150, 0));  // expect 0
    printf("Low rep + 2FA: %d\n", can_access(0, 50, 1));      // expect 0
    printf("No access: %d\n", can_access(0, 50, 0));          // expect 0
    return 0;
}
