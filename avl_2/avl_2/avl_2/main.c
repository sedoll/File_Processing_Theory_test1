#include <stdio.h> 
#include <stdlib.h>

typedef struct AvlNode {
    int data; // key ��
    AvlNode* left_child, * right_child;
}AvlNode;

AvlNode* root;


// LL ȸ�� (���������� ȸ���Ѵ�)

// ��2�� ������ A�� �θ� �ǰ� A->left_child�� B�� child�� �ȴ�.
// A->left�� B�� ������ �ִ� right_child�� �����ϰ� B�� right_child�� A�� �����Ѵ�.

AvlNode* rotate_LL(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = child->right_child;
    child->right_child = parent;
    return child;
}

// RR ȸ�� (�������� ȸ���Ѵ�)

// ��2�� ������ A�� �θ� �ǰ� A->right_child�� B�� child�� �ȴ�.
// A->right�� B�� ������ �ִ� left_child�� �����ϰ� B�� left_child�� A�� �����Ѵ�.

AvlNode* rotate_RR(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = child->left_child;
    child->left_child = parent;
    return child;
}

// RL ȸ�� (������-�������� ȸ���Ѵ�)

// ��2�� ������ A�� �θ� �ǰ� A->right_child�� B�� child�� �ȴ�.
// A->right_child�� rotate_LL(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ������ ȸ��)
// rotate_LL(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_RR(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�. 

AvlNode* rotate_RL(AvlNode* parent)
{
    AvlNode* child = parent->right_child;
    parent->right_child = rotate_LL(child);
    return rotate_RR(parent);
}

// LR ȸ�� (����-���������� ȸ���Ѵ�)

// ��2�� ������ A�� �θ� �ǰ� A->left_child�� B�� child�� �ȴ�.
// A->left_child�� rotate_RR(B)�� ��ȯ�ϴ� ���� �����Ѵ�. (B,C�� ���� ���� ȸ��)
// rotate_RR(B)ȣ��� B�� C�� ��ȭ�� ����� �ٽ� rotate_LL(A)�� ȣ���ϸ� ����Ʈ���� �ȴ�. 

AvlNode* rotate_LR(AvlNode* parent)
{
    AvlNode* child = parent->left_child;
    parent->left_child = rotate_RR(child);
    return rotate_LL(parent);
}

// Ʈ���� ���� ���� �Լ�
// ��ȯȣ��� ������ ���̸� ���ϰ� �̵� �߿��� �� ū���� 1�� ���ϸ� Ʈ���� ���̰� �ȴ�.
int get_height(AvlNode* node)
{
    int height = 0;
    if (node != NULL)
        height = 1 + max(get_height(node->left_child), get_height(node->right_child));
    return height;
}

// ����� �����μ� ��ȯ �Լ�
// ���� ����Ʈ�� ���� - ������ ����Ʈ�� ����
int get_balance(AvlNode* node)
{
    if (node == NULL) return 0;
    return get_height(node->left_child) - get_height(node->right_child);
}

// ���� Ʈ���� ����� �Լ�
AvlNode* balance_tree(AvlNode** node)
{
    int height_diff = get_balance(*node);

    if (height_diff > 1) // ���� ����Ʈ���� ������ �����
    {
        if (get_balance((*node)->left_child) > 0)
            *node = rotate_LL(*node);
        else
            *node = rotate_LR(*node);
    }
    else if (height_diff < -1) // ������ ����Ʈ���� ������ �����
    {
        if (get_balance((*node)->right_child) < 0)
            *node = rotate_RR(*node);
        else
            *node = rotate_RL(*node);
    }
    return *node;
}

// AVL Ʈ���� ���� ����
// key�� ���� ��ȯȣ���� �ݺ��ϹǷν� Ʈ���� ���� �� �� ����ȭ �Լ��� ȣ���Ѵ�.
AvlNode* avl_add(AvlNode** root, int key)
{
    if (*root == NULL)
    {
        *root = (AvlNode*)malloc(sizeof(AvlNode));
        if (*root == NULL)
        {
            printf("�޸� �Ҵ� ����\n");
            exit(-1);
        }

        (*root)->data = key;
        (*root)->left_child = (*root)->right_child = NULL;
    }
    else if (key < (*root)->data)
    {
        (*root)->left_child = avl_add(&((*root)->left_child), key);
        (*root) = balance_tree(root);
    }
    else if (key > (*root)->data)
    {
        (*root)->right_child = avl_add(&((*root)->right_child), key);
        (*root) = balance_tree(root);
    }
    else
    {
        printf("�ߺ� Ű�� ���� ���� ����\n");
        exit(-1);
    }
    return *root;
}

// AVL Ʈ�� Ž�� �Լ�
// �Ϲ� ���� ���� Ʈ���� Ž�� �Լ��� ����. AVL�� ���� Ž�� Ʈ���� �����̴�.
AvlNode* avl_search(AvlNode* node, int key)
{
    if (node == NULL) return NULL;

    printf("%d->", node->data);

    if (key == node->data)
        return node;
    else if (key < node->data)
        avl_search(node->left_child, key);
    else
        avl_search(node->right_child, key);
}

int main()
{
    avl_add(&root, 8);
    avl_add(&root, 9);
    avl_add(&root, 10);
    avl_add(&root, 2);
    avl_add(&root, 1);
    avl_add(&root, 5);
    avl_add(&root, 3);
    avl_add(&root, 6);
    avl_add(&root, 4);
    avl_add(&root, 7);
    avl_add(&root, 11);
    avl_add(&root, 12);

    avl_search(root, 12);

    return 0;
}