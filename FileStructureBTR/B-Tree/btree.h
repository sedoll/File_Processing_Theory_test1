#ifndef __BTREE_H__
#define __BTREE_H__

#define MAX_CHILDREN 3 
#define MAX_KEYS MAX_CHILDREN-1
#define MIN_KEYS (int)(ceil(M/2.0))-1 // 최소 키개수 구하는 식

struct KeyPair
{
    /* B-Tree 노드의 삽입 기준이 되는 인덱스 키 */
    int key;
    /* B-Tree 노드의 키에 연결된 레코드 주소 */
    long offset;
};

struct BTNode
{
    /* 노드가 가진 키의 수 */
    int num_keys;
    /* 노드가 가진 자식 노드의 수 */
    int num_children;
    /* 키 배열 */
    struct KeyPair keys[MAX_KEYS];
    /* 자식 노드 포인터 배열 */
    struct BTNode* children[MAX_CHILDREN];
    // leaf 노드 여부
    bool leaf;
};

struct BTNode* splitNode(int pos, struct BTNode* node, struct BTNode* parent);

struct BTNode* insertNode(int parent_pos, int val, struct BTNode* node, struct BTNode* parent);



/*
 * B-Tree 노드를 생성
 * 메모리를 할당하고 멤버를 초기화 한 뒤
 * 할당된 메모리 주소 반환
 */
struct BTNode* BT_create_node(void);

/*
 * 트리의 루트부터 시작하여 주어진 키를 가지는 노드를 탐색
 * 탐색 성공 시 해당 노드의 주소를 반환
 * 탐색 실패 시 NULL 포인터 반환
 */
struct BTNode* BT_search_key(struct BTNode* root, struct KeyPair k);

/*
 * 트리의 루트부터 시작하여 주어진 키-레코드주소 쌍을 가지는 노드를 삽입
 * 루트 노드를 가리키는 포인터 변수의 주소를 파라미터로 받음
 * 트리에 삽입하고자 하는 키-레코드 쌍을 파라미터로 받음
 * 트리에 삽입하고자 하는 키가 존재하지 않을 경우 새로운 노드를 할당받고 트리에 삽입
 * 삽입 후 리밸런싱 필요
 */
void BT_insert_key(struct BTNode** root, struct KeyPair k);

/*
 * 트리의 루트부터 시작하여 주어진 키를 가지는 노드를 찾아 제거 (메모리 해제)
 * 노드 제거 후 리밸런싱 필요
 */
void BT_remove_key(struct BTNode** root, struct KeyPair k);


#endif #pragma once
