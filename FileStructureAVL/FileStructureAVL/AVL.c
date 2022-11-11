#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "AVL.h"


// AVL 구현

int height(struct AVL_Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Get the balance factor
int getBalance(struct AVL_Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Right rotate
struct AVL_Node* rightRotate(struct AVL_Node* y) {
    struct AVL_Node* x = y->left;
    struct AVL_Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
struct AVL_Node* leftRotate(struct AVL_Node* x) {
    struct AVL_Node* y = x->right;
    struct AVL_Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

/*
 * AVL_Node를 할당
 * 구조체 멤버 초기화
 * 키값은 key로 설정
 * 성공시 AVL_Node 구조체가 할당된 주소 반환
 * 실패시 NULL 반환
 */
struct AVL_Node* AVL_create_node(int key) {
    struct AVL_Node* node = (struct AVL_Node*)malloc(sizeof(struct AVL_Node));
    if (node != NULL)
    {
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
    }
    return node;
}

/*
 * 파라미터로 주어진 AVL_Node를 AVL 트리의 root 노드에 삽입
 * 성공시 0 반환
 * 실패시 (키가 있는 경우) 이외의 값 반환
 */
int AVL_insert_node(struct AVL_Node** root, struct AVL_Node* new_node) {
    // Find the correct position to insertNode the node and insertNode it
    if (*root == NULL) {
        *root = new_node;
        return 0;
    }

    if (new_node->key < (*root)->key) {
        if ((*root)->left == NULL) {
            (*root)->left = new_node;
        }
        else {
            int asd = AVL_insert_node((*root)->left, new_node);
        }
    }
    else if ((new_node->key > (*root)->key)) {
        if ((*root)->right == NULL) {
            (*root)->right = new_node;
        }
        else {
            int asd = AVL_insert_node((*root)->right, new_node);
        }
    }
    else
        return -1;

    // Update the balance factor of each node and
    // Balance the tree
    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));

    int balance = getBalance(*root);
    if (balance > 1 && new_node->key < (*root)->left->key)
        *root = rightRotate(*root);

    if (balance < -1 && new_node->key >(*root)->right->key)
        *root = leftRotate(*root);

    if (balance > 1 && new_node->key > (*root)->left->key) {
        (*root)->left = leftRotate((*root)->left);
        *root = rightRotate(*root);
    }

    if (balance < -1 && new_node->key < (*root)->right->key) {
        (*root)->right = rightRotate((*root)->right);
        *root = leftRotate(*root);
    }

    return 0;
}

/*
 * 트리를 전위순회 하며 노드의 키 값을 순서대로 출력
 * 키 값을 출력하고 탭 문자 (\t) 를 삽입하여 다음 키와 구분
 */
void AVL_print_keys_preorder(struct AVL_Node* root) {
	if (root != NULL) {
		printf("%d\t", root->key);
		AVL_print_keys_preorder(root->left);
		AVL_print_keys_preorder(root->right);
	}
}
