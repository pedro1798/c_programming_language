#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100
void error_handling(char *message);

int main(void) {
    int fd;
    char buf[BUF_SIZE];

    fd = open("data.txt", O_RDONLY); // 파일 열기
    if (fd == -1) {
        error_handling("open() error!");
    }
    printf("file descriptor: %d\n", fd);
    // read() 함수는 읽은 바이트 수를 반환한다.

    if (read(fd, buf, sizeof(buf)) == -1) {
        error_handling("read() error!");
    }
    printf("file descriptor: %d\n", fd);
    close(fd); // 파일 닫기
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr); // 표준 에러 출력
    fputc('\n', stderr); // 줄 바꿈
    exit(1); // 프로그램 종료
}