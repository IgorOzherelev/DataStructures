#include <iostream>
#include <cstdlib>

using namespace std;

struct node
{
	int x;
	int y;
	node * left;
	node * right;

	node (int val)
	{
		x = val;
		y = rand();
		left = NULL;
		right = NULL;
	}

	~node()
	{
		if (left)
			delete left;

		if (right)
			delete right;
	}
};

bool exists(node * root, int key)
{
	if (root == NULL)
		return false;
	if (key == root->x)
		return true;
	if (key > root->x)
		return exists(root->right, key);
	if (key < root->x)
		return exists(root->left, key);
}

pair <node *, node *> split(node * root, int val)
{
	if (root == NULL)
		return {NULL, NULL};

	if (root->x <= val)
	{
		auto res = split(root->right, val);
		root->right = res.first;
		return {root, res.second};
	}

	else
	{
		auto res = split(root->left, val);
		root->left = res.second;

		return {res.first, root};
	}
}

node * merge(node * root1, node * root2)
{
	if (root1 == NULL)
		return root2;
	if (root2 == NULL)
		return root1;

	if (root1->y > root2->y)
	{
		root1->right = merge(root1->right, root2);
		return root1;
	}

	else
	{
		root2->left = merge(root1, root2->left);
		return root2;
	}
}

node * insert(node * root, int val)
{
	if (exists(root, val))
		return root;

	auto res = split(root, val);
	node * newnode = new node(val);
	return merge(merge(res.first, newnode), res.second);
}

node * erase(node * root, int val)
{
	if (!exists(root, val))
		return root;

	auto res1 = split(root, val);
	//res1.first res1.second;

	auto res2 = split(res1.first, val - 1);
	delete res2.second;
	return merge(res2.first, res1.second);
}

int depth(node * root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1 + max(depth(root->left), depth(root->right));
}

void print(node * root)
{
	if (root == NULL)
		return;
	print(root->left);
	cout << root->x << " ";
	print(root->right);
}

int main()
{
	node * root = NULL;
	for (int i = 1; i <= 100; i++)
		root = insert(root, i);

    cout << depth(root) << endl;
    //for (int i = 0; i <= 100; i+=2)
      //  root = erase(root, i);
	//print(root);
	return 0;
}
