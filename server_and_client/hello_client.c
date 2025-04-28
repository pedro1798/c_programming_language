#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    // argc: 인자 개수, argv: 인자 값
    // The first argument (argv[0]) is always the name of the program itself (or the path to the executable).
    // argc는 프로그램 실행 시 전달된 인자의 개수를 나타내고, argv는 인자 값을 문자열 배열로 저장한다.
    // argv[0]: 프로그램 이름, argv[1]: 첫 번째 인자, argv[2]: 두 번째 인자 ...
    
    /*
    For example, if the program is named hello_client and is executed like this:
            ./hello_client 127.0.0.1 8080

    argc will be 3.
    argv[0] will be "./hello_client".
    argv[1] will be "127.0.0.1".
    argv[2] will be "8080".
    */
    
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    if (argc != 3) { // 인자 개수 3개인지 확인
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0); // TCP 소켓 생성  
    if (sock == -1) {// 소켓 생성 실패
        error_handling("socket() error");
    }
    // PF_INET: IPv4 프로토콜 사용
    // SOCK_STREAM: TCP 소켓 사용
    // 0: 기본 프로토콜 사용
    // socket() 함수는 성공하면 소켓 디스크립터를 반환하고, 실패하면 -1을 반환한다.
    // -1은 파일 디스크립터 번호로서 2와 달리 의미가 있는 값이 아니라, 에러 표시를 위해 쓰인다.

    memset(&serv_addr, 0, sizeof(serv_addr)); // 구조체 초기화
    serv_addr.sin_family = AF_INET; // IPv4 프로토콜 사용
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // IP 주소 설정
    serv_addr.sin_port=htons(atoi(argv[2])); // 포트 번호 설정
    // inet_addr(): 문자열을 IP 주소로 변환
    // htons(): host to network short: 호스트 바이트 순서를 네트워크 바이트 순서로 변환.

    /*
    struct sockaddr_in {
        sa_family_t    sin_family;   // 주소 체계 (예: AF_INET)
        in_port_t      sin_port;     // 포트 번호 (2바이트, 네트워크 바이트 순서)
        struct in_addr sin_addr;     // IP 주소
        char           sin_zero[8];  // 패딩 (사용 안 함, 구조체 크기 맞춤용)
    };
    */

    if(connect(sock, (struct sockarr*) &serv_addr, sizeof(serv_addr))==-1) // 서버에 연결
        error_handling("connect() error");
    // connect(): 서버에 연결하는 함수
    // connect() 함수는 성공하면 0을 반환하고, 실패하면 -1을 반환한다.
    // 연결이 성공하면 클라이언트와 서버 간의 연결이 설정된다.
    // 클라이언트와 서버 간의 연결이 설정되면, 클라이언트는 서버에 데이터를 전송할 수 있다.
    // connect() 함수는 서버의 주소 정보를 담은 구조체를 인자로 받는다.
    // 서버의 주소 정보는 connect() 함수가 호출될 때 자동으로 설정된다.
    
    str_len=read(sock, message, sizeof(message)-1); // 서버로부터 데이터 수신
    if(str_len==-1) // read 실패
        error_handling("read() error");

    printf("Message from server: %s \n", message); // 서버로부터 수신한 데이터 출력
    close(sock); // 소켓 닫기
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr); // 에러 메시지 출력
    fputc('\n', stderr); // 줄바꿈
    exit(1);
}