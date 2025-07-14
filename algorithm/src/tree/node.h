#ifndef NODE_H
#define NODE_H

#include <stdlib.h> // for NULL

/**
 * @brief 이진 트리의 노드를 나타내는 구조체
 * 
 * @param data 노드에 저장될 데이터
 * @param left 왼쪽 자식 노드를 가리키는 포인터
 * @param right 오른쪽 자식 노드를 가리키는 포인터
 */
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/**
 * @brief 새로운 트리 노드를 생성하고 초기화합니다.
 * 
 * @param data 새 노드에 저장할 정수 값
 * @return 성공 시 생성된 노드의 포인터를, 실패 시 NULL을 반환합니다.
 */
TreeNode* create_node(int data);

/**
 * @brief 이진 탐색 트리에 데이터를 삽입합니다.
 * 
 * @param root 트리의 루트 노드를 가리키는 포인터의 주소
 * @param data 삽입할 값
 */
void insert_node_bst(TreeNode** root, int data);

/**
 * @brief 트리를 중위 순회하며 노드 데이터를 출력합니다.
 * 
 * @param root 순회할 트리의 루트 노드
 */
void inorder_traversal(TreeNode* root);

/**
 * @brief 지정된 노드와 그 모든 자식 노드들의 메모리를 해제합니다.
 * (후위 순회 방식 사용)
 * 
 * @param node 메모리를 해제할 최상위 노드
 */
void free_tree(TreeNode* node);

/**
 * @brief 트리의 구조를 시각적으로 출력합니다.
 * 
 * @param root 출력할 트리의 루트 노드
 * @param space 들여쓰기를 위한 공간 값 (초기 호출 시 0)
 */
void print_tree_visual(TreeNode* root, int space);


// =======================================================================
// Heap (usually implemented with an array)
// =======================================================================

/**
 * @brief 힙을 나타내는 구조체
 * 
 * @param arr 데이터 저장을 위한 동적 배열 포인터
 * @param count 현재 힙에 저장된 요소의 수
 * @param capacity 힙이 최대로 저장할 수 있는 요소의 수
 */
typedef struct Heap {
    int *arr;
    int count;
    int capacity;
} Heap;

/**
 * @brief 새로운 힙을 생성하고 초기화합니다.
 * 
 * @param capacity 힙의 최대 용량
 * @return 성공 시 생성된 힙의 포인터를, 실패 시 NULL을 반환합니다.
 */
Heap* create_heap(int capacity);

/**
 * @brief 힙의 메모리를 해제합니다.
 * 
 * @param h 해제할 힙의 포인터
 */
void free_heap(Heap* h);

/**
 * @brief 힙의 특정 인덱스에서 아래로 내려가며 힙 속성을 유지합니다. (Min Heap)
 * 
 * @param h 힙의 포인터
 * @param index 시작할 부모 노드의 인덱스
 */
void heapify_down(Heap *h, int index);

/**
 * @brief 힙의 특정 인덱스에서 위로 올라가며 힙 속성을 유지합니다. (Min Heap)
 * 
 * @param h 힙의 포인터
 * @param index 시작할 자식 노드의 인덱스
 */
void heapify_up(Heap *h, int index);

/**
 * @brief 힙에 새로운 데이터를 삽입합니다.
 * 
 * @param h 데이터를 삽입할 힙의 포인터
 * @param data 삽입할 값
 */
void heap_push(Heap* h, int data);

/**
 * @brief 힙에서 최소값(루트)을 제거하고 반환합니다.
 * 
 * @param h 데이터를 제거할 힙의 포인터
 * @return 힙의 최소값. 힙이 비어있으면 -1 (또는 오류 처리)을 반환합니다.
 */
int heap_pop(Heap* h);

/**
 * @brief 힙의 내용을 출력합니다.
 * 
 * @param h 출력할 힙의 포인터
 */
void print_heap(Heap* h);


#endif // NODE_H