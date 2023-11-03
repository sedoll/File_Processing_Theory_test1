#ifndef __BTREE_H__
#define __BTREE_H__

#define MAX_CHILDREN 3 
#define MAX_KEYS MAX_CHILDREN-1
#define MIN_KEYS (int)(ceil(MAX_CHILDREN/2.0))-1 // �ּ� Ű���� ���ϴ� ��

struct KeyPair
{
    /* B-Tree ����� ���� ������ �Ǵ� �ε��� Ű */
    int key;
    /* B-Tree ����� Ű�� ����� ���ڵ� �ּ� */
    long offset;
};

struct BTNode
{
    bool leaf;
    /* ��尡 ���� Ű�� �� */
    int num_keys;
    /* ��尡 ���� �ڽ� ����� �� */
    int num_children;
    /* Ű �迭 */
    struct KeyPair keys[MAX_KEYS];
    /* �ڽ� ��� ������ �迭 */
    struct BTNode* children[MAX_CHILDREN];
};

struct BTNode* splitNode(int pos, struct BTNode* node, struct BTNode* root);

void mNode(struct BTNode* par_node, int node_pos, int mer_node_pos);

void bFLeft(struct BTNode* par_node, int cur_node_pos);

void bFRight(struct BTNode* par_node, int cur_node_pos);

void balNode(struct BTNode* node, int child_pos);

int mChildNode(struct BTNode* par_node, int cur_node_pos);

int findPredecessor(struct BTNode* cur_node);

int overridePredecessor(struct BTNode* par_node, int pos_std_search);

int findSuccessor(struct BTNode* cur_node);

int overrideSuccessor(struct BTNode* par_node, int pos_std_search);

void deleteInnerNode(struct BTNode* cur_node, int cur_node_pos);

int deleteValFromNode(int val, struct BTNode* node);

/*
 * B-Tree ��带 ����
 * �޸𸮸� �Ҵ��ϰ� ����� �ʱ�ȭ �� ��
 * �Ҵ�� �޸� �ּ� ��ȯ
 */
struct BTNode* BT_create_node(void);

/*
 * Ʈ���� ��Ʈ���� �����Ͽ� �־��� Ű�� ������ ��带 Ž��
 * Ž�� ���� �� �ش� ����� �ּҸ� ��ȯ
 * Ž�� ���� �� NULL ������ ��ȯ
 */
struct BTNode* BT_search_key(struct BTNode* root, struct KeyPair k);

/*
 * Ʈ���� ��Ʈ���� �����Ͽ� �־��� Ű-���ڵ��ּ� ���� ������ ��带 ����
 * ��Ʈ ��带 ����Ű�� ������ ������ �ּҸ� �Ķ���ͷ� ����
 * Ʈ���� �����ϰ��� �ϴ� Ű-���ڵ� ���� �Ķ���ͷ� ����
 * Ʈ���� �����ϰ��� �ϴ� Ű�� �������� ���� ��� ���ο� ��带 �Ҵ�ް� Ʈ���� ����
 * ���� �� ���뷱�� �ʿ�
 */
void BT_insert_key(struct BTNode** root, struct KeyPair k);

/*
 * Ʈ���� ��Ʈ���� �����Ͽ� �־��� Ű�� ������ ��带 ã�� ���� (�޸� ����)
 * ��� ���� �� ���뷱�� �ʿ�
 */
void BT_remove_key(struct BTNode** root, struct KeyPair k);


#endif #pragma once
