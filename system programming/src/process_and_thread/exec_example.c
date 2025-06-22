#include <unistd.h>
#include <stdio.h>

int main() {
    printf("I'm going to run /bin/ls\n");
    // execl은 현재 프로세스를 새로운 프로그램으로 대체한다.
    // int execl(const char *path, const char *arg0, ..., NULL);
    /*
    •	path: 실행할 프로그램의 절대 경로
	•	arg0: 프로그램 이름 (전통적으로 argv[0])
	•	arg1, arg2, ...: 실행 인자들 (argv[1], argv[2], ...)
	•	마지막은 반드시 NULL
    */
    execl("/bin/ls", "ls", "-l", NULL);
    /*
    "/bin/ls" : 실행할 ELF 바이너리 (파일 시스템 상의 프로그램)
    "ls" : argv[0] (일반적으로 프로그램 이름)
    "-l" : argv[1] → 옵션
    NULL : 인자 종료 표시
    */
    // execl은 실행되면 이 아래는 안 출력됨.

    printf("This won't print\n");
    return 0;
}