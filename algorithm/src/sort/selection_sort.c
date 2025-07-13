#include <stdio.h>
#include <stdlib.h>

// 두 정수의 값을 교환하는 유틸리티 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * 선택 정렬 (Selection Sort)
 * - 배열을 순회하면서 각 위치에 들어갈 가장 작은 값을 찾습니다.
 * - 배열의 0번 인덱스부터 시작하여, 전체 배열에서 가장 작은 값을 찾아 0번 인덱스의 값과 교환합니다.
 * - 다음으로 1번 인덱스부터 시작하여, 남은 배열 부분에서 가장 작은 값을 찾아 1번 인덱스의 값과 교환합니다.
 * - 이 과정을 배열의 끝까지 반복합니다.
 * - 시간 복잡도: O(n^2)
 */
void selection_sort(int* arr, int size) {
    int i, j, min_idx;

    // 배열의 각 위치를 순회 (마지막 요소는 자동으로 정렬됨)
    for (i = 0; i < size - 1; i++) {
        // 현재 위치(i)를 최소값의 인덱스로 가정
        min_idx = i;
        // i+1 부터 배열의 끝까지 순회하며 실제 최소값의 인덱스를 찾음
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // 찾은 ���소값과 현재 위치(i)의 값을 교환
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 선택 정렬 함수 호출 (원본 배열이 직접 수정됨)
    selection_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
