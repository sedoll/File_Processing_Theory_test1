#include "btree.h"

#include <stdlib.h>
#include <string.h> 

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
    // 노드 삽입 구현 
}

void BT_remove_key(struct BTNode** root, struct KeyPair k)
{
    // 노드 삭제 구현 
}

struct BTNode* BT_search_key(struct BTNode* root, struct KeyPair k)
{
    // 노드 탐색 구현 
    return NULL;
}