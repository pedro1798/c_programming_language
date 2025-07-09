#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int target, int size) {
    int left = 0; int right = size - 1; 
    if (left > right) {
        return -1;
    } else {
        int mid = (left + right) / 2; // 몫만 반환
        printf("left: %d, right: %d, mid: %d\n", left, right, mid);
        if (arr[mid] == target) {
            return mid; 
        } else if (arr[mid] < target) {
            return binary_search(arr + mid + 1, target, size - mid - 1); // 오른쪽 절반 탐색
        } else {
            return binary_search(arr, target, mid); // 왼쪽 절반 탐색   
        }
    }
}

int main() {
    int length;
    scanf("%d\n", &length);

    int *arr = (int *)malloc(length * sizeof(int));
    
    for (int i = 0; i < length; i++) {
        scanf("%d", &arr[i]);
    }

    int target;
    scanf("%d", &target);

    printf("찾는 값 인덱스: %d\n", binary_search(arr, target, length));
}