#include <stdio.h>
#include <unistd.h>
/* 시스템 콜의 결과가 x86-64 아키텍처에서는 rax 레지스터에 저장된다. */

int main() {
    pid_t pid = fork(); // 시스템 콜

    if (pid == 0) {
        printf("Child: fork() returned %d\n", pid);
    } else {
        printf("Parent: fork() returned %d(Child PID)\n", pid);
    }
    /* 
    이 코드에서 pid 변수는 사실 rax의 복사본이다.
    fork()는 내부적으로 커널이 반환한 rax 값을 그대로 리턴하고, 
    그걸 pid에 저장하기 때문.
    */
    return 0;
}