#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int x = 100;
    pid_t pid = fork();

    if (pid == 0) {
        // 자식 프로세스라면
        x = 200; // COW 발생
        printf("Child PID %d: x = %d (%p)\n", getpid(), x, (void*)&x);
    } else {
        wait(NULL); // 자식 프로세스가 끝날 때까지 기다림
        printf("Parent PID %d: x = %d (%p)\n", getpid(), x, (void*)&x);
    }
    return 0;
}