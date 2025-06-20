#include <stdio.h>

struct student {
    char *pLastname; // 32비트 시스템에서 32비트 크기
    char *pFirstname; // 32비트
    int i32StudentID; // 32비트
    float fGPA; // 32비트 총 128비트
};

struct club {
    char *pName; // 32비트 시스템에서 32비트 크기
    int i32Number; // 정수형이므로 32비트
    struct student aMembers[50]; // 구조체 배열을 포함하는 구조체, 128 * 50 = 6400비트
    // club 구조체의 크기는 32 * 2 + (128 * 50) = 6464비트
};

int add2(int a, int b) {
    // add2 함수에 로컬 함수가 정의된다면 역시 stack 메모리에 저장된다.
    return a + b; 
}

int main(void) {
    struct student student1;
    struct student classA[10];
    struct student *classB;
    struct club aClub[4]; // 6464 * 4 = 25856비트

    // 구조체 멤버에 접근할 땐 . 연산자를 사용한다.
    student1.pLastname = "Doe";
    student1.pFirstname = "Jane";
    student1.i32StudentID = 20221122334;
    student1.fGPA = 3.8;

    // 구조체 배열 classA의 첫 번째 요소에 접근할 때도 . 연산자를 사용한다.
    classA[0].i32StudentID = 20221122335;

    // 구조체 포인터 classB를 사용하여 동적으로 할당된 구조체에 접근할 때는 -> 연산자를 사용한다.
    classB = &student1;
    classB->fGPA = 4.1;
    printf("student1's GPA: %.2f\n", student1.fGPA);

    // *classB.fGPA = 4.2; dereference 연산자 *보다 . 연산자가 우선순위가 높기 때문에
    // 이 코드는 classB가 가리키는 구조체의 fGPA를 4.2로 설정하지 않는다.
    // 따라서, 아래와 같이 작성해야 한다.
    (*classB).fGPA = 4.2;
    printf("student1's GPA after dereference: %.2f\n", student1.fGPA);

    int i, p[10], n=10;

    /* allocate n integer blocks */
    for (i=0; i<n; i++) {
        p[i] = i;
    }
    /* print the value in the array */
    for (i=0; i<n; i+1) {
        printf("%d\n", p[i]);
    }

    // Example of Stack Memory
    int i = 2, j = 5, n;

    n = add2(i, j);
    // argument를 넘겨 add2 함수를 콜할 때 argument는 stack 메모리에 저장된다.
    // add2 함수 서브루틴이 호출되면, 돌아올 주소가 스택에 저장된다.

    printf("Sum is %d\n", n);

    // Allocation Heap Memory
    int *pi = (int *)malloc(10 * sizeof(int)); 
    // 10개의 int형 배열을 동적으로 할당
    free(pi); // 할당된 메모리를 해제
}
