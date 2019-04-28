#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

void build(int * tree, int * mass, unsigned int vertex, unsigned int left, unsigned int right)
{
	if (left == right)
		tree[vertex] = mass[left];

	else
	{
		unsigned int mid = (left + right) / 2;
		build(tree, mass, vertex * 2, left, mid);
		build(tree, mass, vertex * 2 + 1, mid + 1, right);
		tree[vertex] = tree[vertex * 2] + tree[vertex * 2 + 1];
	}
}

int sum(int * tree, int * mass, unsigned int vertex, unsigned int left, unsigned int right, unsigned int l, unsigned int r)
{
	if (l > r)
		return 0;
	if (l == left && r == right)
		return tree[vertex];

	unsigned int mid = (left + right) / 2;
	return sum(tree, mass, vertex * 2, left, mid, l, min(r, mid)) + sum(tree, mass, vertex * 2 + 1,  mid + 1, right, max(l, mid + 1), r);
}

void update(int * tree, unsigned int vertex, unsigned int left, unsigned int right, unsigned int position, int val)
{
	if (left == right)
		tree[vertex] = val;
	else
	{
		unsigned int mid = (left + right) / 2;

		if (mid >= position)
			update(tree, vertex * 2, left, mid, position, val);
		else
			update(tree, vertex * 2 + 1, mid + 1, right, position, val);

		tree[vertex] = tree[vertex * 2] + tree[vertex * 2 + 1];
	}
}

int main()
{
	const unsigned int n = 4;
	static int tree[4 * n];
	int mass[] = {10, 20, 77, 55};

	build(tree, mass, 1, 0, n - 1);
	int res = sum(tree, mass, 1, 0, n - 1, 0, 2);
	cout << res << endl;

	return 0;
}

