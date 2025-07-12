#include <stdio.h>
#include <stdlib.h>

/*
 * [개선된 방식]
 * 이 merge 함수는 결과를 반환하는 대신, 미리 할당된 임시 배열(temp)을 사용하여
 * 정렬된 내용을 저장한 뒤, 마지막에 원본 배열(arr)에 그 결과를 덮어씁니다.
 * 이로써 불필요한 메모리 할당이 사라집니다.
 */
void merge(int* arr, int* temp, int left_start, int mid, int right_end) {
    int left_end = mid;
    int right_start = mid + 1;
    // temp 배열의 시작 인덱스를 left_start로 지정하여 전체 temp 배열을 효율적으로 활용
    int index = left_start;

    while (left_start <= left_end && right_start <= right_end) {
        if (arr[left_start] <= arr[right_start]) {
            temp[index++] = arr[left_start++];
        } else {
            temp[index++] = arr[right_start++];
        }
    }

    while (left_start <= left_end) {
        temp[index++] = arr[left_start++];
    }

    while (right_start <= right_end) {
        temp[index++] = arr[right_start++];
    }

    // 정렬된 temp 배열의 내용을 다시 원본 arr 배열의 해당 위치로 복사
    // for 루프의 범위�� 병합된 부분의 실제 길이(right_end - left_start + 1)만큼만 순회
    for (int i = left_start; i <= right_end; ++i) {
        arr[i] = temp[i];
    }
}

// 실제 재귀 호출을 담당하는 헬퍼(helper) 함수
void merge_sort_recursive(int* arr, int* temp, int left, int right) {
    if (left >= right) {
        return;
    }

    // [개선점 3: 안전한 중간 지점 계산]
    // int mid = (left + right) / 2; 방식은 left와 right가 매우 클 경우
    // 정수 오버플로우(Integer Overflow)를 일으킬 수 있습니다.
    // 아래 방식은 오버플로우를 방지하는 안전한 계산법입니다.
    int mid = left + (right - left) / 2;

    merge_sort_recursive(arr, temp, left, mid);
    merge_sort_recursive(arr, temp, mid + 1, right);

    // 정렬된 두 부분을 병합
    merge(arr, temp, left, mid, right);
}

/*
 * [개선점 1: 효율적인 메모리 관리]
 * 정렬에 필요한 임시 배열(temp)을 단 한 번만 할당하고,
 * 이 배열을 재귀 함수에 계속 전달하여 재사용합니다.
 * 이를 통해 수많은 malloc/free 호출을 제거하여 성능을 크게 향상시킵니다.
 *
 * [개선점 2: In-Place 방식과 래퍼(Wrapper) 함수]
 * 이 함수는 원본 배열을 직접 수정(in-place)하며, 사용자에게 간단한 인터페이스를 제공하는 래퍼(wrapper) 역할을 합니다.
 * 사용자는 복잡한 재귀 구현(merge_sort_recursive)을 알 필요 없이 이 함수만 호출하면 됩니다.
 * 이는 C 표준 라이브러리(qsort)와 유사한 관례적인 방식입니다.
 */
void merge_sort(int* arr, int size) {
    if (size < 2) {
        return;
    }
    int* temp = (int*)malloc(size * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // 실제 재귀 로직은 헬퍼 함수에 위임
    merge_sort_recursive(arr, temp, 0, size - 1);

    // 단 한 번의 메모리 해제
    free(temp);
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

    /*
     * [개선된 방식의 장점]
     * - 함수 호출이 간단해짐 (merge_sort(arr, n) 호출로 끝).
     * - 원본 배열이 직접 정렬되므로 별도의 포인터가 필요 없음.
     * - 메모리 관리가 단순해짐 (arr에 대한 free() 호출 한 번으로 충분).
     */
    merge_sort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}