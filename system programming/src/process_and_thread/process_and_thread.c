#include <pthread.h>
/* 표준 입출력 라이브러리입니다. */
#include <stdio.h>
/* 유닉스 시스템 콜과 관련된 함수들을 정의합니다. */
#include <unistd.h>
/* 일반적인 유틸리티 함수들을 포함합니다. */
#include <stdlib.h>
/* 자식 프로세스의 종료 상태를 추적할 때 사용하는 함수들을 포함합니다. */
#include <sys/wait.h>

void* thread_func(void *arg) {  // 새 쓰레드가 실행할 함수
    /* getpid(): 현재 프로세스의 PID 반환 */
    /* 같은 프로세스 내에 생성된 쓰레드는 PID는 동일하다 */
    printf("In thread, PID = %d\n", getpid());
    /* C에선 void*로 암시적 캐스팅 가능하다. C++에선 안 됨. */
    int* result = malloc(sizeof(int));
    *result = 123;
    return result; // 쓰레드가 반환할 값
}

int main() {
    pthread_t thread;
    printf("Main PID = %d\n", getpid());
    /*
    int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
    */
    int* ret_val;
    pthread_create(&thread, NULL, thread_func, NULL);

    /* int pthread_join(pthread_t thread, void **retval); 
    이 호출은 해당 쓰레드가 끝날 때까지 main 함수가 대기하게 만든다.
    없으면 메인 함수가 먼저 종료되어 프로그램이 비정상적으로 끝날 수도 있다. */
    pthread_join(thread, (void**)&ret_val);

    printf("Thread returned valud: %d\n", *ret_val);
    
    free(ret_val); // 쓰레드가 반환한 메모리 해제
    return 0;
}