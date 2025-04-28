#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
void error_handling(char *message);

int main(void) {
    int fd; // 파일 디스크립터
    char buf[] = "Let's go!\n";

    // fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC); // 파일 열기
    fd = open("data.txt", O_CREAT | O_WRONLY | O_APPEND); // 파일 열기
    if (fd == -1) {
        error_handling("open() error!");
    }
    printf("file descriptor: %d\n", fd);
    
    if (write(fd, buf, sizeof(buf)) == -1) { // 파일에 쓰기
        error_handling("write() error!");
    }
    close(fd); // 파일 닫기
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr); // 표준 에러 출력
    fputc('\n', stderr); // 줄 바꿈
    exit(1); // 프로그램 종료
}