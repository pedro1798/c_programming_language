#include <stdio.h>
struct student {
    char *pLastname;
    char *pFirstname;
    int i32StudentID;
    float fGPA;
};

int main(void) {
    struct student student1;
    struct student classA[10];
    struct student *classB;
}
