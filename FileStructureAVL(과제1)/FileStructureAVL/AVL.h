#ifndef __AVL_H__
#define __AVL_H__

struct AVL_Node 
{
	int key; 
	struct AVL_Node* left; //왼쪽
	struct AVL_Node* right; //오른쪽
	struct AVL_Node* Parent; //부모
	// 다른 멤버 추가 가능 
};

/*
 * AVL_Node를 할당
 * 구조체 멤버 초기화 
 * 키값은 key로 설정 
 * 성공시 AVL_Node 구조체가 할당된 주소 반환 
 * 실패시 NULL 반환 
 */
struct AVL_Node* AVL_create_node(int key);

/*
 * 파라미터로 주어진 AVL_Node를 AVL 트리의 root 노드에 삽입
 * 성공시 0 반환 
 * 실패시 (키가 있는 경우) 이외의 값 반환 
 */
int AVL_insert_node(struct AVL_Node* root, struct AVL_Node* new_node);

/*
 * 트리를 전위순회 하며 노드의 키 값을 순서대로 출력
 * 키 값을 출력하고 탭 문자 (\t) 를 삽입하여 다음 키와 구분
 */
void AVL_print_keys_preorder(struct AVL_Node* root);

#endif 