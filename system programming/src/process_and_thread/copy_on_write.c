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
    /* &x 주소 (%p)는 같아 보일 수 있음 (논리 주소) 
    물리 메모리는 처음엔 공유 -> 이후 분리됨(서로 다른 페이지에 존재) 
    
    ✅ 실제 COW 발생 흐름
	1.	fork() 실행
	부모와 자식이 같은 물리 메모리 페이지를 공유 (읽기 전용으로)
	2.	자식이 x = 200; 수행 → 쓰기 시도
	3.	CPU가 페이지 보호 예외(page fault) 발생시킴
	4.	커널이:
	- 그 페이지를 복사
	- 자식 쪽 페이지 테이블을 새 복사본으로 바꿈
	- 쓰기 가능으로 설정
	5.	자식은 복사된 페이지에 x = 200 저장

    논리 주소(Virtual Address)는 페이지 테이블을 통해 
    다른 물리 주소(Physical Address)로 프로세스마다 다르게 매핑되기 때문에, 
    같은 논리 주소라도 서로 다른 프로세스에서는 다른 물리 주소를 가리킬 수 있다.
    각 프로세스마다 고유하게 가지는 페이지 테이블이 다르기 때문!
    논리 주소 <-> 물리 주소 매핑이 독립적으로 존재함.
    */

    return 0;
}