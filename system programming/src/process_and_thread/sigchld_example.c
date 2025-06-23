/* 
리눅스에서 자식 프로세스를 만들고, 
그 자식이 종료되었을 때 SIGCHLD 시그널을 처리해서 
좀비 프로세스를 방지하는 예제.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void sigchld_handler(int signum) {
    int status; // 자식 프로세스의 종료 상태를 담을 변수입니다.
    // 자식 프로세스의 종료 상태 회수
    // -1 : 모든 자식 프로세스 중 아무나 하나를 기다린다.
    // WNOHANG : 자식 프로세스가 종료되지 않았으면 즉시 반환하도록 한다. 블로킹되지 않는다.
    // 즉, WNOHANG을 쓰면 부모가 자식이 아직 안 죽었는데도 무한히 기다리지 않고 돌아온다.

    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("자식 프로세스 종료됨: PID=%d\n", pid);
}

int main() {
    // 부모 프로세스는 시그널 핸들러 등록
    // 자식이 종료되면 커널은 부모에게 SIGCHLD 시그널을 보낸다.
    // 부모는 등록된 핸들러를 호출하여 waitpid()로 자식의 종료 상태를 회수한다.
    // 부모는 계속 살아있으며, 자식의 종료를 적절히 처리했기 때문에 좀비 프로세스가 발생하지 않는다.
    signal(SIGCHLD, sigchld_handler);
    
    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid == 0) {
        //자식 프로세스
        printf("자식 프로세스 실행 중\n");
        sleep(1);
        exit(0); // 자식 프로세스 종료
    } else {
        // 부모 프로세스
        printf("부모 프로세스 실행 중, 자식 PID=%d\n", pid);
        while (1) {
            // 부모 프로세스는 계속 실행 중
            sleep(5);
        }
    }
}