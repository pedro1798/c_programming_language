#include <stdlib.h>
#include <stdio.h>

void main() {
    int i, *p, n = 10, m = 20;

    /* allocate n integer blocks */
    if ((p = (int *)malloc(n * sizeof(int))) == NULL) {
        /* 메모리 할당 실패시 -1(NULL) 값을 리턴한다. */
        /* malloc은 실패할 수 있기 때문에 if문으로 에러처리 하는 것.*/
        perror("malloc memory allocation failed");
        exit(0);
    }
    for (i = 0; i < n; i++) {
        p[i] = i;
    }
    /* add m bytes to end of p block */
    if ((p = (int *)realloc(p, (n + m) * sizeof(int))) == NULL) {
        perror("realloc memory allocation failed.");
        exit(0);
    }
    for (i = n; i < n + m; i++) {
        p[i] = i;
    }
    /* print new array */
    for (i = 0; i < n + m; i++) {
        printf("%d\n", p[i]);
    }
    
    free(p);  /* return p to available memory pool */
}