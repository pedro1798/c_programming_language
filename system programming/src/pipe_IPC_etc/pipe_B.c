// pipe_B.c
#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // 개행 제거

    if (strcmp(input, "1234") == 0) {
        printf("Access granted!\n");
        return 0;
    } else {
        printf("Access denied.\n");
        return 1;
    }
}