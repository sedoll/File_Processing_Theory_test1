#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "AVL.h"


// AVL 구현

// 높이 계산
int height(struct AVL_Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 밸런스 팩터 계산
int getBalance(struct AVL_Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// 오른쪽 회전
struct AVL_Node* rightRotate(struct AVL_Node* b) {
    struct AVL_Node* a = b->left;
    struct AVL_Node* t = a->right;

    a->right = b;
    b->left = t;

    b->height = max(height(b->left), height(b->right)) + 1;
    a->height = max(height(a->left), height(a->right)) + 1;

    return a;
}

// 왼쪽 회전
struct AVL_Node* leftRotate(struct AVL_Node* a) {
    struct AVL_Node* b = a->right;
    struct AVL_Node* t = b->left;

    b->left = a;
    a->right = t;

    a->height = max(height(a->left), height(a->right)) + 1;
    b->height = max(height(b->left), height(b->right)) + 1;

    return b;
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
    if (*root == NULL) { // 처음 값을 대입
        *root = new_node;
    }
    else { // 이후의 값을 대입
        if (new_node->key < (*root)->key) { // 부모 보다 키값이 작은 경우
            AVL_insert_node(&(*root)->left, new_node); // 부모노드 왼쪽에 넣음
        }
        else if ((new_node->key > (*root)->key)) { // 부모 보다 키값이 큰 경우
            AVL_insert_node(&(*root)->right, new_node); // 부모노드 오른쪽에 넣음
        }
        else { // 같은 경우, 연산 안하고 종료
            return -1;
        }

        (*root)->height = 1 + max(height((*root)->left), height((*root)->right)); // 높이 계산

        int balance = getBalance(*root); // 밸런스 팩터 값 대입
        if (balance > 1 && new_node->key < (*root)->left->key) { // LL삽입
            *root = rightRotate((*root));
        }

        if (balance < -1 && new_node->key >(*root)->right->key) { // RR삽입
            *root = leftRotate((*root));
        }

        if (balance > 1 && new_node->key > (*root)->left->key) { // LR삽입
            (*root)->left = leftRotate((*root)->left);
            *root = rightRotate((*root));
        }

        if (balance < -1 && new_node->key < (*root)->right->key) { // RL삽입
            (*root)->right = rightRotate((*root)->right);
            *root = leftRotate((*root));
        }
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
