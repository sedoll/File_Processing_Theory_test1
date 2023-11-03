#include "btree.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

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

struct BTNode* splitNode(int pos, struct BTNode* node, struct BTNode* root) {
    int median;
    median = node->num_keys / 2; 
    struct BTNode* right_node; 

    right_node = (struct BTNode*)malloc(sizeof(struct BTNode));
    right_node->leaf = node->leaf;
    right_node->num_keys = 0;
    right_node->num_children = 0;

    int num_iter = node->num_keys;
    for (int i = median + 1; i < num_iter; i++) { 
        right_node->keys[i - (median + 1)] = node->keys[i];
        right_node->num_keys++;
        node->num_keys--;
    }

    if (!node->leaf) { 
        num_iter = node->num_children;
        for (int i = median + 1; i < num_iter; i++) {
            right_node->children[i - (median + 1)] = node->children[i];
            right_node->num_children++;
            node->num_children--;
        }
    }

    if (node == root) { 
        struct BTNode* new_parent_node;
        new_parent_node = BT_create_node();
        node->num_keys--;
        new_parent_node->children[0] = node; 
        new_parent_node->children[1] = right_node;

        new_parent_node->num_children = 2;
        return new_parent_node;
    }
    else {
        for (int i = root->num_keys; i > pos; i--) {
            root->keys[i] = root->keys[i - 1];
            root->children[i + 1] = root->children[i];
        }

        root->keys[pos] = node->keys[median]; 
        root->num_keys++;
        node->num_keys--;
        root->children[pos + 1] = right_node; 
        root->num_children += 1;
    }
    return node; 
}

struct BTNode* insertNode(int parent_pos, int val, struct BTNode* node, struct BTNode* root) { 
    int pos; 
    for (pos = 0; pos < node->num_keys; pos++) {
        if (val == node->keys[pos].key) {
            return node;
        }
        else if (val < node->keys[pos].key) { 
            break;
        }
    }
    if (!node->leaf) { 
        node->children[pos] = insertNode(pos, val, node->children[pos], node);
        if (node->num_keys == MAX_KEYS + 1) { 
            node = splitNode(parent_pos, node, root); 
        }
    }
    else { 
        for (int i = node->num_keys; i > pos; i--) { 
            node->keys[i] = node->keys[i - 1]; 
            node->children[i + 1] = node->children[i]; 
        }

        node->keys[pos].key = val; 
        node->num_keys++;
        if (node->num_keys == MAX_KEYS + 1) { 
            node = splitNode(parent_pos, node, root);
        }
    }
    return node;
}

void BT_insert_key(struct BTNode** root, struct KeyPair k)
{
    if (!*root) { 
        *root = BT_create_node();
        (*root)->num_keys = 1;
        (*root)->leaf = true;
        (*root)->keys[0].key = k.key;
        (*root)->keys[0].offset = k.offset;
    }
    else { 
        *root = insertNode(0, k.key, *root, *root);
    }
    
}

void mNode(struct BTNode* par_node, int node_pos, int mer_node_pos) {
    int merge_idx = par_node->children[mer_node_pos]->num_keys;
    par_node->children[mer_node_pos]->keys[merge_idx] = par_node->keys[mer_node_pos];
    par_node->children[mer_node_pos]->num_keys++;

    for (int i = 0; i < par_node->children[node_pos]->num_keys; i++) {
        par_node->children[mer_node_pos]->keys[merge_idx + 1 + i] = par_node->children[node_pos]->keys[i]; 
        par_node->children[mer_node_pos]->num_keys++;
    }

    int merge_childidx = par_node->children[mer_node_pos]->num_children;
    for (int i = 0; i < par_node->children[node_pos]->num_children; i++) {
        par_node->children[mer_node_pos]->children[merge_childidx + i] = par_node->children[node_pos]->children[i];
        par_node->children[mer_node_pos]->num_children++;
    }

    free(par_node->children[node_pos]);

    for (int i = mer_node_pos; i < (par_node->num_keys) - 1; i++) {
        par_node->keys[i] = par_node->keys[i + 1];
    }
    par_node->num_keys--;

    for (int i = mer_node_pos + 1; i < (par_node->num_children) - 1; i++) {
        par_node->children[i] = par_node->children[i + 1];
    }
    par_node->num_children--;
}

void bFLeft(struct BTNode* par_node, int cur_node_pos) { 
    int tenant_idx = 0; 

    for (int i = 0; i < par_node->children[cur_node_pos]->num_keys; i++) {
        par_node->children[cur_node_pos]->keys[i + 1] = par_node->children[cur_node_pos]->keys[i];
    }
    par_node->children[cur_node_pos]->keys[tenant_idx] = par_node->keys[cur_node_pos - 1]; 
    par_node->children[cur_node_pos]->num_keys++;

    int idx_from_sib_topar = (par_node->children[cur_node_pos - 1]->num_keys) - 1; 
    par_node->keys[cur_node_pos - 1] = par_node->children[cur_node_pos - 1]->keys[idx_from_sib_topar]; 
    par_node->children[cur_node_pos - 1]->num_keys--;

    if (par_node->children[cur_node_pos - 1]->num_children > 0) { 
        int tenant_childidx = (par_node->children[cur_node_pos - 1]->num_children) - 1; 

        for (int i = par_node->children[cur_node_pos]->num_children; i > 0; i--) { 
            par_node->children[cur_node_pos]->children[i] = par_node->children[cur_node_pos]->children[i - 1];
        }

        par_node->children[cur_node_pos]->children[0] = par_node->children[cur_node_pos - 1]->children[tenant_childidx]; 
        par_node->children[cur_node_pos]->num_children++;

        par_node->children[cur_node_pos - 1]->num_children--;
    }
}

void bFRight(struct BTNode* par_node, int cur_node_pos) { 
    int tenant_idx = par_node->children[cur_node_pos]->num_keys; 
    par_node->children[cur_node_pos]->keys[tenant_idx] = par_node->keys[cur_node_pos]; 
    par_node->children[cur_node_pos]->num_keys++;

    int idx_from_sib_topar = 0;
    par_node->keys[cur_node_pos] = par_node->children[cur_node_pos + 1]->keys[idx_from_sib_topar]; 

    for (int i = 0; i < (par_node->children[cur_node_pos + 1]->num_keys) - 1; i++) {
        par_node->children[cur_node_pos + 1]->keys[i] = par_node->children[cur_node_pos + 1]->keys[i + 1];
    }
    par_node->children[cur_node_pos + 1]->num_keys--;

    int idx_from_sib = 0;
    if (par_node->children[cur_node_pos + 1]->num_children > 0) { 
        int tenant_childidx = par_node->children[cur_node_pos]->num_children; 
        par_node->children[cur_node_pos]->children[tenant_childidx] = par_node->children[cur_node_pos + 1]->children[idx_from_sib];
        par_node->children[cur_node_pos]->num_children++;

        for (int i = 0; i < par_node->children[cur_node_pos + 1]->num_children - 1; i++) {
            par_node->children[cur_node_pos + 1]->children[i] = par_node->children[cur_node_pos + 1]->children[i + 1];
        }
        par_node->children[cur_node_pos + 1]->num_children--;
    }
}

void balNode(struct BTNode* node, int child_pos) { 
    if (child_pos == 0) { 
        if (node->children[child_pos + 1]->num_keys > MIN_KEYS) { 
            bFRight(node, child_pos);
        }
        else { 
            mNode(node, child_pos + 1, child_pos);
        }
        return;
    }

    else if (child_pos == (node->num_keys)) { 
        if (node->children[child_pos - 1]->num_keys > MIN_KEYS) { 
            bFLeft(node, child_pos);
        }
        else { 
            mNode(node, child_pos, child_pos - 1); 
        }
        return;
    }
    else { 
        if (node->children[child_pos - 1]->num_keys > MIN_KEYS) {
            bFLeft(node, child_pos);
        }
        else if (node->children[child_pos + 1]->num_keys > MIN_KEYS) {
            bFRight(node, child_pos);
        }
        else {
            mNode(node, child_pos, child_pos - 1); 
        }
        return;
    }
}

int mChildNode(struct BTNode* par_node, int cur_node_pos) {
    int mergeidx = par_node->children[cur_node_pos]->num_keys; 

    int val_par_node = par_node->keys[cur_node_pos].key; 
    par_node->children[cur_node_pos]->keys[mergeidx] = par_node->keys[cur_node_pos];
    par_node->children[cur_node_pos]->num_keys++;

    for (int i = 0; i < par_node->children[cur_node_pos + 1]->num_keys; i++) {
        par_node->children[cur_node_pos]->keys[mergeidx + 1 + i] = par_node->children[cur_node_pos + 1]->keys[i];
        par_node->children[cur_node_pos]->num_keys++;
    }

    for (int i = 0; i < par_node->children[cur_node_pos + 1]->num_children; i++) {
        par_node->children[cur_node_pos]->children[mergeidx + 1 + i] = par_node->children[cur_node_pos + 1]->children[i];
        par_node->children[cur_node_pos]->num_children++;
    }

    for (int i = cur_node_pos; i < par_node->num_keys; i++) {
        par_node->keys[i] = par_node->keys[i + 1];
        par_node->num_keys--;
    }
    for (int i = cur_node_pos + 1; i < par_node->num_children; i++) {
        par_node->children[i] = par_node->children[i + 1];
        par_node->num_children--;
    }
    return val_par_node;

}

int findPredecessor(struct BTNode* cur_node) {
    int predecessor;
    if (cur_node->leaf) { 
        return cur_node->keys[cur_node->num_keys - 1].key; 
    }
    return findPredecessor(cur_node->children[(cur_node->num_children) - 1]); 
}

int overridePredecessor(struct BTNode* par_node, int pos_std_search) {
    int predecessor = findPredecessor(par_node->children[pos_std_search]); 
    par_node->keys[pos_std_search].key = predecessor;
    return predecessor;
}

int findSuccessor(struct BTNode* cur_node) {
    int successor;
    if (cur_node->leaf) {
        return cur_node->keys[0].key; 
    }
    return findSuccessor(cur_node->children[0]); 
}

int overrideSuccessor(struct BTNode* par_node, int pos_std_search) {
    int successor = findSuccessor(par_node->children[pos_std_search + 1]); 
    par_node->keys[pos_std_search].key = successor; 
    return successor;
}

void deleteInnerNode(struct BTNode* cur_node, int cur_node_pos) {
    int cessor = 0; 
    int deletion_for_merge = 0;

    if (cur_node->children[cur_node_pos]->num_keys >= cur_node->children[cur_node_pos + 1]->num_keys) {
        if (cur_node->children[cur_node_pos]->num_keys > MIN_KEYS) {
            cessor = overridePredecessor(cur_node, cur_node_pos);
            deleteValFromNode(cessor, cur_node->children[cur_node_pos]); 
        }
        else {
            deletion_for_merge = mChildNode(cur_node, cur_node_pos);
            deleteValFromNode(deletion_for_merge, cur_node->children[cur_node_pos]);
        }
    }
    else {
        if (cur_node->children[cur_node_pos + 1]->num_keys > MIN_KEYS) {
            cessor = overrideSuccessor(cur_node, cur_node_pos);
            deleteValFromNode(cessor, cur_node->children[cur_node_pos + 1]); 
        }
        else {
            deletion_for_merge = mChildNode(cur_node, cur_node_pos);
            deleteValFromNode(deletion_for_merge, cur_node->children[cur_node_pos]);
        }

    }

}

int deleteValFromNode(int val, struct BTNode* node) {
    int pos; 
    int flag = false; 
    for (pos = 0; pos < node->num_keys; pos++) {
        if (val == node->keys[pos].key) { 
            flag = true;
            break;
        }
        else if (val < node->keys[pos].key) { 
            break;
        }
    } 
    if (flag) {
        if (node->leaf) {  
            for (int i = pos; i < node->num_keys; i++) { 
                node->keys[i] = node->keys[i + 1]; 
            }
            node->num_keys--;
        }
        else { 
            deleteInnerNode(node, pos); 
        }
        return flag;
    }
    else { 
        if (node->leaf) { 
            return flag;
        }
        else { 
            flag = deleteValFromNode(val, node->children[pos]); 
        }
    }
    if (node->children[pos]->num_keys < MIN_KEYS) { 
        balNode(node, pos); 
    }

    return flag;
}

void BT_remove_key(struct BTNode** root, struct KeyPair k)
{
    if (!*root) { 
        return;
    }
    int flag = deleteValFromNode(k.key, *root); 
    if (!flag) { 
        return;
    }
    if ((*root)->num_keys == 0) {  
        *root = (*root)->children[0]; 
    }
}

struct BTNode* BT_search_key(struct BTNode* root, struct KeyPair k)
{
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