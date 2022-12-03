#include "btree.h"

#include <stdlib.h>
#include <string.h> 


// 오버로딩 시켜서 짜볼까?
struct BTNode* BT_create_node(void)
{
    struct BTNode* new_node = (struct BTNode*)malloc(sizeof(struct BTNode));
    if (new_node == NULL) {
        // alloc failed 
        return NULL;
    }
    new_node->num_keys = 0;
    new_node->num_children = 0;
    memset(new_node->keys, 0x00, sizeof(new_node->keys));
    memset(new_node->children, 0x00, sizeof(struct BTNode*) * MAX_CHILDREN);
    return new_node;
}

void BT_insert_key(struct BTNode** root, struct KeyPair k)
{
    if (!*root) { // root가 없으면
        *root = BT_create_node(); // root를 만들어라.
        (*root)->num_keys = 1;
        (*root)->keys[0] = k;
    }
    else { // 루트가 있으면
        (*root)->num_keys += 1;
        if ((*root)->num_keys <= MAX_KEYS) {
            
        }
    }
}

void BT_remove_key(struct BTNode** root, struct KeyPair k)
{
    //// 노드 삭제 구현
    //if (!*root) { // 현재 보는 노드에 아예 값이 없으면
    //    printf("Empty tree!!\n");
    //    return;
    //}
    //int flag = deleteValFromNode(k.key, *root); // 현재 노드 내에서 값을 지우는 함수 호출. 지우는 값이랑 현재 노드를 인자로 받음. 리턴은 flag로 받음.
    //if (!flag) { // flag가 0이면 실행.
    //    printf("%d does not exist in this tree. \n", k.key); // 함수 내에서 못찾으면 플래그가 0인거니까 에러 메세지 출력
    //    return;
    //}
    //if ((*root)->keys == 0) {  // deleteVal을 하고 나서 node의 키개수가 0일 때 = 현재 노드에 아무것도 없어서 변화가 필요함.
    //    *root = (*root)->children[0]; // 지금 노드를 가장 왼쪽 자식 노드로 만듬.
    //}
    //root = &*root;
}

struct BTNode* BT_search_key(struct BTNode* root, struct KeyPair k)
{
    // 노드 탐색 구현 
    if (!root) {
        return NULL;
    }
    while (true) {
        int pos;
        for (pos = 0; pos < root->num_keys; pos++) {
            if (k.key == root->keys[pos].key) {
                return root;
            }
            else if (k.key < root->keys[pos].key) {
                break;
            }
        }
        if (root->num_children) break;
        root = root->children[pos];
    }

    return NULL;
}