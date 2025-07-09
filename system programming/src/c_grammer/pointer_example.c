#include <stdio.h>
int main(void) {
    int a = 10;
    int *b = &a;
    printf("Size of b: %zu bytes\n", sizeof(b));
    printf("Value of b: %d\n", *b);
    *b = 32;
    printf("Value of b: %d\n", *b);
    printf("address of a: %p\n", (void*)&a);
    printf("Hello, World!\n");
    return 0;
}
