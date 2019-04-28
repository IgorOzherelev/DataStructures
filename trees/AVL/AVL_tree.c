#include <stdio.h>
#include <stdlib.h>


struct Node 
{
   int key;
   int high;
   struct Node *left;
   struct Node *right;
};


void preOrder(struct Node *node);
void postOrder(struct Node *node);
void inOrder(struct Node *node);

int Height(struct Node *p);
int Bfactor(struct Node* p);
void FixHeight(struct Node* p);

struct Node* RotateRight(struct Node* p);
struct Node* RotateLeft(struct Node* p);
struct Node* Balance(struct Node* p);

struct Node* tree_add(struct Node *node, int x);
struct Node* Tree_Search(struct Node *node, int val);

struct Node* MIN(struct Node *node);
struct Node* MAX(struct Node *node);

void DeleteNode(struct Node *node, int x);
void Tree_delete(struct Node *tree);

int main()
{
	
	struct Node *tree = NULL;
	
	tree = tree_add(tree, 7);
	tree = tree_add(tree, 3);
	tree = tree_add(tree, 2);
	tree = tree_add(tree, 1);
	tree = tree_add(tree, 9);
	tree = tree_add(tree, 5);
	tree = tree_add(tree, 4);
	tree = tree_add(tree, 6);
	tree = tree_add(tree, 8);
	
	printf("preOrder: ");
	preOrder(tree);
	printf("\n");
	
	printf("postOrder: ");
	postOrder(tree);
	printf("\n");
	
	printf("inOrder: ");
	inOrder(tree);
	printf("\n");
	
	printf("%d\n", MIN(tree)->key);
	printf("%d\n", MAX(tree)->key);
	
	if (Tree_Search(tree, 7))
	{
		printf("search 7: 7 is here\n");
	}
	
	
	Tree_delete(tree);
	
	return 0;
}

void preOrder(struct Node *node)
{
	if (node == NULL)
	{
		return;
	}
	
	printf("%d ", node->key);
	preOrder(node->left);
	preOrder(node->right);
}

void postOrder(struct Node *node)
{
	if (node == NULL)
	{
		return;
	}
	
	postOrder(node->left);
	postOrder(node->right);
	printf("%d ", node->key);
}

void inOrder(struct Node *node)
{
	if (node == NULL)
	{
		return;
	}
	
	inOrder(node->left);
	printf("%d ", node->key);
	inOrder(node->right);
}

int Height(struct Node *p)
{
	return p?p->high:0;
}

int Bfactor(struct Node* p)
{
	return Height(p->right) - Height(p->left);
}

void FixHeight(struct Node* p)
{
	int hl = Height(p->left);
	int hr = Height(p->right);
	p->high = (hl>hr?hl:hr) + 1;
}

struct Node* RotateRight(struct Node* p)
{
	struct Node *q = p->left;
	
	p->left = q->right;
	q->right = p;
	
	FixHeight(p);
	FixHeight(q);
	
	return q;
}

struct Node* RotateLeft(struct Node* q)
{
	struct Node *p = q->right;
	
	q->right = p->left;
	p->left = q;
	
	FixHeight(q);
	FixHeight(p);
	
	return p;
}

struct Node* Balance(struct Node* p)
{
	FixHeight(p);
	
	if (Bfactor(p) == 1)
	{
		if (Bfactor(p->right) < 0)
		{
			p->right = RotateRight(p->right);
		}
		
		return RotateLeft(p);
	}
	
	if (Bfactor(p) == -1)
	{
		if (Bfactor(p->left) > 0)
		{
			p->left = RotateLeft(p->left);
		}
		
		return RotateRight(p);
	}
	
	return p;
}

struct Node* tree_add(struct Node *p, int x)
{
	if (p == NULL) 
	{
		p = malloc (sizeof(struct Node));
		p->key = x;
		p->high = 0;
		p->left = p->right = NULL;
	} 
	
	else if (x < p->key)
	{
		p->left = tree_add(p->left, x);
		p->left->high = p->high + 1;		
	}

	else if (x > p->key)
	{
		p->right = tree_add(p->right, x);
		p->right->high = p->high + 1;		
	}

	
	return Balance(p);
}



struct Node* Tree_Search(struct Node *node, int val)
{
	while (node && val != node->key)
	{
		if (val < node->key)
		{
			node = node->left;
		}
		
		else
		{
			node = node->right;
		}
	}
	
	return node;
}

struct Node* MIN(struct Node *node)
{
	struct Node* min;
	
	while (node->left)
	{
		node = node->left;
	}
	
	min = node; 
	
	return min;
}

struct Node* MAX(struct Node *node)
{
	struct Node* max;
	
	while (node->right)
	{
		node = node->right;
	}
	
	max = node;
	
	return max;
}

void Tree_delete(struct Node *tree)
{
	if (tree == NULL)
	{
		return;
	}
	
	Tree_delete(tree->left);
	free(tree);
	Tree_delete(tree->right);
}
