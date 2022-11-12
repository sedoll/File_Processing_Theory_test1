#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>

#include "AVL.h"

#define MAX_TEST_COUNT 10
#define MAX_KEY_RANGE 100 

void mytest(void)
{
	struct AVL_Node* mytree = NULL;

	int rand_key = 0;
	int i; 
	printf("입력 노드: ");
	// 랜덤 시드 초기화 
	srand((unsigned int) time(NULL));
	for (i = 0; i < MAX_TEST_COUNT; i++) {
		struct AVL_Node* new_node = NULL;

		// 랜덤 키 생성 
		rand_key = rand() % MAX_KEY_RANGE;

		// 노드 생성 
		new_node = AVL_create_node(rand_key);
		printf("%d ", rand_key);

		// 노드 삽입
		if (AVL_insert_node(&mytree, new_node) != 0) {
			// 삽입 실패시 생성한 노드 삭제 
			free(new_node);
		}
	}

	if (mytree) {
		printf("\nAVL 전위순회 출력:\t");
		AVL_print_keys_preorder(mytree);
	}
}

int main(void)
{
	mytest();

	return 0;
}