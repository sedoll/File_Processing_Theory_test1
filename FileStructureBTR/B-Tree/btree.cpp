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
    if (!root) {
        return NULL;
    }
    struct KeyPair k2 = k;
    struct BTNode* level = root;
    while (true) {
        int pos;
        for (pos = 0; pos < level->num_keys; pos++) {
            if ( k2 == level->keys[pos]) {
                return ;
            }
            else if (k->key < level->keys[pos]) {
                break;
            }
        }
        if (level->num_children) break;
        level = level->children[pos];
    }

    return NULL;
}