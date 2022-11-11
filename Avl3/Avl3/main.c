#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    char* value;
    struct node* left;
    struct node* right;
};

struct node* new_node(char* content)
{
    struct node* result = (struct node*)malloc(sizeof(struct node));
    if (result != NULL)
    {
        result->left = NULL;
        result->right = NULL;
        result->value = content;
    }
    return result;
}

void printtabs(int numtab)
{
    for (int i = 0; i < numtab; i++)
    {
        printf("\t");
    }
}

void show_tree(struct node* root, int level)
{
    if (root == NULL)
    {
        printtabs(level);
        printf("= -<empty>\n");
        return;
    }
    printtabs(level);
    printf("= %s\n", root->value);

    printtabs(level);
    printf("\tleft\n");
    show_tree(root->left, level + 1);

    printtabs(level);
    printf("\tright\n");
    show_tree(root->right, level + 1);
}

void show_t(struct node* root)
{
    show_tree(root, 0);
}

bool add_value(struct node** pointer_to_root, char* val)
{
    //ponteiro para um [ponteiro de ponteiro]
    struct node* root = *pointer_to_root;
    if (root == NULL) {
        (*pointer_to_root) = new_node(val);
        return true;
    }
    //se valor adicionado menor que o valor nesse atual node
    if (strcmp(val, root->value) < 0)
    {
        return add_value(&(root->left), val);
    }
    //se valor adicionado MAIOR que atual
    else if (strcmp(val, root->value) > 0)
    {
        return add_value(&(root->right), val);
    }
    else
    {
        printf("\nnew_node IGUAL node existente = %s\n", root->value);
        return false;
    }
}

bool search(struct node* root, char* val)
{
    if (root == NULL) return false;

    //se valor adicionado menor que o valor nesse atual node
    if (strcmp(val, root->value) < 0)
    {
        return search(root->left, val);
    }
    //se valor adicionado MAIOR que atual
    else if (strcmp(val, root->value) > 0)
    {
        return search(root->right, val);
    }
    else
    {
        return true;
    }
}

int main()
{
    struct node* node_root = NULL;
    add_value(&node_root, "new, words");
    add_value(&node_root, "new, word");
    add_value(&node_root, "new, woRD");

    show_t(node_root);

    free(node_root);

    return 0;
}