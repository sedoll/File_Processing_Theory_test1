#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "AVL.h"

// 높이 계산
int height(struct AVL_Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// AVL 구현
struct AVL_Node* AVL_create_node(int key) { // 노드 생성
    struct AVL_Node* node = (struct AVL_Node*)malloc(sizeof(struct AVL_Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// 오른쪽 회전
struct AVL_Node* rightRotate(struct AVL_Node* y) {
    struct AVL_Node* x = y->left;
    struct AVL_Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// 왼쪽 회전
struct AVL_Node* leftRotate(struct AVL_Node* x) {
    struct AVL_Node* y = x->right;
    struct AVL_Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 밸런스 팩터 (-1, 0, 1) 이면 회전 x
int getBalance(struct AVL_Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


int AVL_insert_node(struct AVL_Node** root, struct AVL_Node* new_node) { // 노드 삽입
    if (*root == NULL)
        return (new_node->key);

    if (new_node->key < *root)
        (*root)->left = insertNode((*root)->left, new_node->key);
    else if (*root > new_node->key)
        (*root)->right = insertNode((*root)->right, new_node->key);
    else
        return root;

    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));

    int balance = getBalance(root);
    if (balance > 1 && new_node->key < (*root)->left->key)
        return rightRotate(root);

    if (balance < -1 && new_node->key >(*root)->right->key)
        return leftRotate(root);

    if (balance > 1 && new_node->key > (*root)->left->key) {
        (*root)->left = leftRotate((*root)->left);
        return rightRotate(root);
    }

    if (balance < -1 && new_node->key < (*root)->right->key) {
        (*root)->right = rightRotate((*root)->right);
        return leftRotate(root);
    }

    return root;
}

void AVL_print_keys_preorder(struct AVL_Node* root) { // 전위 순회 출력
    if (root != NULL) {
        printf("%d\t", root->key); // 키값 출력
        AVL_print_keys_Preorder(root->left); // 왼쪽 서브트리로 이동
        AVL_print_keys_Preorder(root->right); // 오른쪽 서브트리로 이동
    }
}