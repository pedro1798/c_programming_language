#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock; // 서버 소켓 디스크립터
    int clnt_sock; // 클라이언트와 연결돈 소켓 디스크립터 

    struct sockaddr_in serv_addr; // 서버 주소 구조체(바인딩에 사용)
    struct sockaddr_in clnt_addr; // client 주소 구조체. accept에서 채워짐
    socklen_t clnt_addr_size; // 구조체의 크기 (in/out parameter)
    /*
    •	in parameter: 함수에 값을 전달만 하는 파라미터 (입력 용도)
	•	out parameter: 함수가 결과를 해당 파라미터를 통해 “되돌려 주는” 파라미터 (출력 용도)
	•	in/out parameter: 함수에 값을 주고, 함수가 그걸 수정해서 되돌려주는 역할
    */

    /*
    struct sockaddr_in {
    sa_family_t    sin_family;   // 주소 체계(AF_INET)
    in_port_t      sin_port;     // 포트번호 (네트워크 바이트 오더)
    struct in_addr sin_addr;     // IP 주소 (네트워크 바이트 오더)
    char           sin_zero[8];  // padding (안 쓰는 공간)
    };
    */
    char message[] = "Hello World!";

    if(argc!=2) {
      printf("Usage : %s <port>\n", argv[0]);
      exit(1);  
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성
    // PF_INET: IPv4 프로토콜 사용한단 의미. <sys/socket.h>에 정의된 매크로 상수.
    // SOCK_STREAM: TCP 소켓 사용. <sys/socket.h>에 정의된 매크로 상수.
    // 0: 기본 프로토콜 사용
    // 표준적으로는 AF_INET을 더 권장
    if(serv_sock == -1) {// 소켓 생성 실패
        error_handling("socket() error");
    }
    // socket() 함수는 성공하면 소켓 디스크립터를 반환하고, 실패하면 -1을 반환한다.
    // 소켓 디스크립터는 소켓을 식별하는 정수값이다.

    memset(&serv_addr, 0, sizeof(serv_addr)); // 구조체 초기화
    serv_addr.sin_family=AF_INET; // IPv4 프로토콜 사용
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // 모든 IP 주소에서 수신
    serv_addr.sin_port=htons(atoi(argv[1])); // 포트 번호 설정
    // htons(): host to network short: 호스트 바이트 순서를 네트워크 바이트 순서로 변환
    // INADDR_ANY: 모든 IP 주소를 의미. 매크로 상수 0 <-> (0.0.0.0)
    // atoi(): 문자열을 정수로 변환.
    // serv_addr 구조체는 서버의 주소 정보를 담고 있다.

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)  // bind, 실패하면 에러처리
        error_handling("bind() error");

    if(listen(serv_sock, 5)==-1) // 리슨, 실패하면 에러처리
        error_handling("listen() error");
    // listen(): 클라이언트의 연결 요청을 대기하는 함수
    // 5: 최대 대기 큐 길이
    // listen() 함수는 성공하면 0을 반환하고, 실패하면 -1을 반환한다.
    // 클라이언트의 연결 요청을 대기하는 상태가 된다.
    // 클라이언트가 연결 요청을 하면 accept() 함수가 호출된다.
    // accept() 함수는 클라이언트의 연결 요청을 수락하고, 클라이언트와의 연결을 위한 소켓을 생성한다.
    // accept() 함수는 클라이언트의 주소 정보를 담은 구조체를 인자로 받는다.
    // 클라이언트의 주소 정보는 accept() 함수가 호출될 때 자동으로 설정된다.

    clnt_addr_size=sizeof(clnt_addr); // 클라이언트 주소 구조체 크기
    // 	•accept()는 클라이언트가 접속 요청을 보내올 때까지 기다리는 함수야.
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); // 클라이언트 연결 수락
    if(clnt_sock==-1) // accept 실패
        error_handling("accept() error");

    write(clnt_sock, message, sizeof(message)); 
    // 클라이언트에게 데이터 전송. accept를 지나서 이 명령어가 실행되었다는건 연결요청이 있었다는 뜻이 된다.
    close(clnt_sock); // 클라이언트 소켓 닫기
    close(serv_sock); // 서버 소켓 닫기 
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr); // 에러 메시지를 표준 에러로 출력
    fputc('\n', stderr); // 줄바꿈
    exit(1); // 프로그램 종료
};

// 오류 메시지 처리할 때 자주 사용되는 방식
// char *message: 함수 인자로 문자열 포인터를 하나 받는다.