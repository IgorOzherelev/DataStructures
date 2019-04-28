#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node
{
    struct Node *left;
    struct Node *right;
    int key;
    size_t color;
    struct Node *parent;
};

struct Node* leftRotate(struct Node *root,struct Node *node);
struct Node* rightRotate(struct Node *root, struct Node *node);
struct Node* balanceTree(struct Node *root, struct Node *node);
struct Node* treeAdd(struct Node *root, int val);
void print(struct Node *root);

void main()
{
    struct Node *root = NULL;
    root = treeAdd(root, 7);
    root = treeAdd(root, 5);
    root = treeAdd(root, 8);
    root = treeAdd(root, 9);
    root = treeAdd(root, 6);
    root = treeAdd(root, 1);


    print(root);
}


struct Node* leftRotate(struct Node *root, struct Node *node)
{
    struct Node *right = node->right;

    node->right = right->left;

    if (right->left != NULL)
    {
        right->left->parent = node;
    }

    if (right != NULL)
    {
        right->parent = node->parent;
    }

    if (node->parent != NULL)
    {
        if (node == node->parent->left)
        {
            node->parent->left = right;
        }

        else
        {
            node->parent->right = right;
        }
    }

    else
    {
        root = right;
    }

    right->left = node;
    if (node != NULL)
    {
        node->parent = right;
    }

    return root;
}

struct Node* rightRotate(struct Node *root, struct Node *node)
{
    struct Node *left = node->left;

    node->left = left->right;
    if (left->right != NULL)
    {
        left->right->parent = node;
    }

    if (left != NULL)
    {
        left->parent = node->parent;
    }

    if (node->parent != NULL)
    {
        if (node == node->parent->right)
        {
            node->parent->right = left;
        }

        else
        {
            node->parent->left = left;
        }
    }

    else
    {
        root = left;
    }

    left->right = node;

    if (node != NULL)
    {
        node->parent = left;
    }

    return root;
}
struct Node* balanceTree(struct Node *root, struct Node *node)
{
    struct Node *uncle;

    while (node != root && node->parent->color == RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            uncle = node->parent->parent->right;

            if (uncle->color == RED)
            {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }

            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    root = leftRotate(root, node);
                }

                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                root = rightRotate(root, node->parent->parent);
            }
        }

        else
        {
                uncle = node->parent->parent->left;
                if (uncle->color == RED)
                {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }

                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        root = rightRotate(root, node);
                    }

                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;

                    root = leftRotate(root, node->parent->parent);
                }
        }
    }

    root->color = BLACK;

    return root;
}


struct Node* treeAdd(struct Node *root, int val)
{

    struct Node *node, *parent = NULL;

    node = root;
    while (node != NULL)
    {
        parent = node;
        if (val < node->key)
        {
            node = node->left;
        }

        else if (val > node->key)
            node = node->right;

        else
            return root;
    }

    node = malloc(sizeof(struct Node));
    node->key = val;
    node->color = RED;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    if (parent != NULL)
    {
        if (val < parent->key)
        {
            parent->left = node;
        }

        else
        {
            parent->right = node;
        }
    }

    else
    {
        root = node;
    }

    return balanceTree(root, node);
}

void print(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    else
    {
        printf("%d:%d ", root->key, root->color);
        print(root->left);
        print(root->right);
    }
}
