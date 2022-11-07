#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "AVL.h"

// AVL 구현
struct AVL_Node* AVL_create_node(int key) { // 노드 생성
    struct AVL_Node* node = (struct AVL_Node*)malloc(sizeof(struct AVL_Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

int AVL_insert_node(struct AVL_Node** root, struct AVL_Node* new_node) { // 노드 삽입
    if (root == NULL)
        return (new_node->key);

    if (new_node->key < root)
        node->left = insertNode(node->left, key);
    else if (root > new_node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
        height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL_print_keys_preorder(struct AVL_Node* root) { // 전위 순회 출력
    if (root != NULL) {
        printf("%d\t", root->key); // 키값 출력
        AVL_print_keys_Preorder(root->left); // 왼쪽 서브트리로 이동
        AVL_print_keys_Preorder(root->right); // 오른쪽 서브트리로 이동
    }
}