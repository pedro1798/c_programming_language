#include <stdio.h>
#include <stdlib.h>
#include "node.h"

// 'TreeNode' 구조체는 "node.h"에 정의되어 있으므로 여기서는 제거합니다.

/**
 * @brief 새로운 트리 노드를 생성하고 초기화합니다.
 * @note node.h에 선언되어 있습니다.
 */
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * @brief 이진 탐색 트리에 데이터를 삽입합니다.
 * @note node.h에 선언되어 있습니다.
 */
void insert_node(TreeNode** root, int data) {
    if (*root == NULL) {
        *root = create_node(data);
    } else if (data < (*root)->data) {
        insert_node(&((*root)->left), data);
    } else {
        insert_node(&((*root)->right), data);
    }
}

/**
 * @brief 트리를 중위 순회하며 노드 데이터를 출력합니다.
 * @note node.h에 선언되어 있습니다.
 */
void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

/**
 * @brief 지정된 노드와 그 모든 자식 노드들의 메모리를 해제합니다.
 * @note node.h에 선언되어 있습니다.
 */
void free_tree(TreeNode* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

/**
 * @brief 트리의 구조를 시각적으로 출력합니다.
 * @note node.h에 선언되어 있습니다.
 */
void print_tree_visual(TreeNode* root, int space) {
    if (root == NULL) return;

    space += 10;

    print_tree_visual(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    print_tree_visual(root->left, space);
}
