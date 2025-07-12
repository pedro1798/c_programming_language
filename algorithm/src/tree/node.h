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
void insert_node(TreeNode** root, int data);

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


#endif // NODE_H