#include <stdio.h>
#include <stdlib.h>

// 두 정수의 값을 교환하는 유틸리티 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * 버블 정렬 (Bubble Sort)
 * - 인접한 두 요소를 비교하여, 정렬 순서에 맞지 않으면 위치를 교환합니다.
 * - 배열의 처음부터 끝까지 이 과정을 반복하면, 가장 큰 요소가 배열의 맨 끝으로 이동하게 됩니다 (거품처럼).
 * - 한 번의 순회가 끝날 때마다 가장 큰 값이 제자리를 찾으므로, 다음 순회에서는 비교 범위를 하나씩 줄여나갑니다.
 * - 시간 복잡도: O(n^2)
 */
void bubble_sort(int* arr, int size) {
    int i, j;
    // 총 size-1 번의 순회를 수행
    for (i = 0; i < size - 1; i++) {
        // 각 순회마다 인접한 요소를 비교
        // (i가 증가할수록 뒤쪽의 요소들은 이미 정렬된 상태이므로 비교 범위가 줄어듦)
        for (j = 0; j < size - i - 1; j++) {
            // 앞의 요소가 뒤의 요소보다 크면 교환
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
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

    // 버블 정렬 함수 호출 (원본 배열이 직접 수정됨)
    bubble_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
