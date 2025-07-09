// pipe_A.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int try_password(const char *password) {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();
    if (pid == 0) {
        // 자식 프로세스
        close(pipefd[1]); // write 닫기
        dup2(pipefd[0], 0); // stdin으로 설정
        close(pipefd[0]);

        execl("./pipe_B", "pipe_B", NULL);
        perror("execl 실패");
        exit(1);
    } else {
        // 부모 프로세스
        close(pipefd[0]); // read 닫기
        write(pipefd[1], password, strlen(password));
        write(pipefd[1], "\n", 1); // fgets 때문에 줄바꿈 필요
        close(pipefd[1]);

        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }
}

int main() {
    char guess[10];
    for (int i = 0; i <= 9999; i++) {
        snprintf(guess, sizeof(guess), "%04d", i);
        printf("Trying: %s\n", guess);

        if (try_password(guess)) {
            printf("Password found: %s\n", guess);
            break;
        }
    }
    return 0;
}