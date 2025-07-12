#include <stdio.h>
#include <stdlib.h>

/*
 * [개선점 1: 비효율적인 메모리 할당]
 * 이 merge 함수는 호출될 때마다 정렬된 결과를 담을 새로운 메모리(sorted)를 할당합니다.
 * 재귀 호출이 깊어질수록 수많은 작은 메모리 할당과 해제가 반복되어 성능 저하의 주요 원인이 됩니다.
 */
int* merge(int* left, int left_len, int* right, int right_len) {
    int* sorted = malloc(sizeof(int) * (left_len + right_len));
    int i = 0, j = 0, k = 0;

    while (i < left_len && j < right_len) {
        if (left[i] <= right[j]) {
            sorted[k++] = left[i++];
        } else {
            sorted[k++] = right[j++];
        }
    }

    while (i < left_len) {
        sorted[k++] = left[i++];
    }

    while (j < right_len) {
        sorted[k++] = right[j++];
    }

    return sorted;
}

/*
 * [개선점 2: 새로운 배열 반환 방식]
 * 이 함수는 정렬된 '새로운' 배열을 반환합니다.
 * 이로 인해 호출자는 원본 배열(arr)과 정렬된 배열(result)을 모두 관리해�� 하며,
 * 메모리도 두 배로 사용하게 됩니다. C의 표준적인 정렬 함수들은 보통 원본 배열을 직접 수정합니다.
 *
 * [개선점 1 (연관): 비효율적인 메모리 할당]
 * 재귀의 가장 깊은 단계(size == 1)에서도 불필요한 메모리 할당이 발생합니다.
 */
int* merge_sort(int* arr, int size) {
    if (size == 1) {
        int* single = malloc(sizeof(int));
        single[0] = arr[0];
        return single;
    }

    // 중간 지점을 계산합니다. 이 방식은 간단하지만, 인덱스 기반 재귀 호출에서는
    // left와 right의 합이 int의 표현 범위를 넘는 오버플로우가 발생할 수 있습니다.
    // (better_merge_sort.c에서 사용된 `left + (right - left) / 2` 방식 참고)
    int mid = size / 2;
    // 재귀 호출이 반복될수록 수많은 메모리 할당/해제가 발생함
    int* left = merge_sort(arr, mid);
    int* right = merge_sort(arr + mid, size - mid);
    int* result = merge(left, mid, right, size - mid);

    // 할당된 중간 단계의 배열들을 해제해야 함
    free(left);
    free(right);

    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    /*
     * [개선점 2 (연관): 복잡한 메모리 관리]
     * 원본 배열(arr)과 정렬된 배열(sorted)을 별도로 관리해야 하므로
     * 두 번의 free() 호출이 필요합니다. 코드가 복잡해지고 실수할 가능성이 높아집니다.
     */
    int* sorted = merge_sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", sorted[i]);
    }

    free(arr);
    free(sorted);

    return 0;
}
