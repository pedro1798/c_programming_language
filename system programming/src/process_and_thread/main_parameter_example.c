#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc); // argc는 인자의 개수

    // argv는 인자들의 배열 (문자열 포인터 배열)
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}