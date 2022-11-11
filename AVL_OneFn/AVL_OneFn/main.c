#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>

#define MAX_TEST_COUNT 5
#define MAX_KEY_RANGE 100

int cnt = 1;

struct AVL_Node
{
    int key;
    struct AVL_Node* left;
    struct AVL_Node* right;
    int height;
    // 다른 멤버 추가 가능 
};

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
    if (!*root) {
        *root = calloc(sizeof * *root, 1);
        (*root)->key = new_node->key;
        (*root)->height = 1;
    }
    else if (new_node->key < (*root)->key) {
        AVL_insert_node(&(*root)->left, new_node);
        (*root)->height = (*root)->left->height + 1;
        getBalance(*root);
    }
    else if (new_node->key > (*root)->key) {
        AVL_insert_node(&(*root)->right, new_node);
        (*root)->height = (*root)->right->height + 1;
        getBalance(*root);
    }

    return 0;
}

void AVL_print_keys_preorder(struct AVL_Node* root) { // 전위 순회 출력
    if (root != NULL) {
        printf("%d\t", root->key); // 키값 출력
        AVL_print_keys_preorder(root->left); // 왼쪽 서브트리로 이동
        AVL_print_keys_Preorder(root->right); // 오른쪽 서브트리로 이동
    }
}

void mytest(void)
{
	struct AVL_Node* mytree = NULL;

	int rand_key = 0;
	int i;

	// 랜덤 시드 초기화 
	srand((unsigned int)time(NULL));
	for (i = 0; i < MAX_TEST_COUNT; i++) {
		struct AVL_Node* new_node = NULL;

		// 랜덤 키 생성 
		rand_key = rand() % MAX_KEY_RANGE;

		// 노드 생성 
		new_node = AVL_create_node(rand_key);
        printf("%d %d\n", rand_key, i);

		// 노드 삽입
		if (AVL_insert_node(&mytree, new_node) != 0) {
			// 삽입 실패시 생성한 노드 삭제 
			free(new_node);
		}
	}

	if (mytree) {
		AVL_print_keys_preorder(mytree);
	}
}

int main(void)
{
	mytest();

	return 0;
}