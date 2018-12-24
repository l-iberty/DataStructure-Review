#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include "tree.h"
#include "bintree.h"

using namespace std;

#define MAX_NODE 14

// 4.4.5 (7) 已知一棵树的层次序列和每个节点的度, 构建该树的孩子-兄弟链表
void build_sibling_child_list(TreeNode node[], int degree[], int n)
{
	int i, j, k, child;

	child = 1;
	for (i = 0; i < n; i++)
	{
		if (degree[i] > 0)
		{
			node[i]->child = node[child];
			for (j = child, k = 1; k < degree[i]; j++, k++)
			{
				node[j]->sibling = node[j + 1];
			}
			child = j + 1;
		}
	}
}

// 4.5.4 (6) 判断给定的二叉树是否为二叉查找树
bool is_bstree(BinTree T)
{
	if (T == NULL)
		return false; // 规定: 空树不是 Binary Search Tree

	if (T->left == NULL && T->right == NULL)
		return true;

	if (T->left && T->right)
	{
		if (T->left->data < T->data && T->right->data > T->data)
			return (is_bstree(T->left) && is_bstree(T->right));
		else
			return false;
	}
	else if (T->left)
	{
		if (T->left->data < T->data)
			return is_bstree(T->left);
		else
			return false;
	}
	else
	{
		if (T->right->data > T->data)
			return is_bstree(T->right);
		else
			return false;
	}
}

// 4.5.4 (7) 求指定节点在二叉查找树中的层次
int get_level(BSTree T, int x)
{
#if 0
	// 以下代码为王道的解答, 如果 x 不在 T 中则会出错
	int level = 0;

	if (T != NULL)
	{
		level++;
		while (T->data != x)
		{
			if (x < T->data)
				T = T->left;
			else
				T = T->right;
			level++;
		}
	}
	return level;
#endif

	int level = 0;
	if (T != NULL)
	{
		level++;
		while (T != NULL)
		{
			if (x == T->data)
				return level;
			if (x < T->data)
				T = T->left;
			else
				T = T->right;
			level++;
		}
		if (T == NULL)
			level = 0; // not found
	}
	return level;
}

// 4.5.4 (8) 判断二叉树是否为二叉平衡树
void is_avltree(BinTree T, bool &balanced, int &h)
{
	bool left_b = false, right_b = false; // 左右子树的平衡标记
	int left_h = 0, right_h = 0; // 左右子树的高度

	if (T == NULL)
	{
		h = 0;
		balanced = true;
	}
	else if (T->left == NULL && T->right == NULL)
	{
		h = 1;
		balanced = true;
	}
	else
	{
		is_avltree(T->left, left_b, left_h);
		is_avltree(T->right, right_b, right_h);
		h = max(left_h, right_h) + 1;
		if (abs(left_h - right_h) < 2)
			balanced = (left_b && right_b);
		else
			balanced = false;
	}
}

// 4.5.4 (10) 从大到小输出二叉查找树中所有其值不小于 k 的关键字
void print_keys(BSTree T, int k)
{
	if (T != NULL)
	{
		print_keys(T->right, k);
		if (T->data >= k)
		{
			printf("%d ", T->data);
		}
		print_keys(T->left, k);
	}
}

void print_path(stack<BinTree> &s)
{
	stack<BinTree> s1 = stack<BinTree>(s);
	stack<BinTree> stack;
	while (!s1.empty())
	{
		stack.push(s1.top());
		s1.pop();
	}
	while (!stack.empty())
	{
		printf("%d ", stack.top()->data);
		stack.pop();
	}
	printf("\n");
}

// p183 <思维扩展>
void get_path(BinTree T, int data, stack<BinTree> &stack, int &sum)
{
	if (T != NULL)
	{
		stack.push(T);
		sum += T->data;
		if (T->left == NULL && T->right == NULL // 叶子节点
			&& sum == data)
		{
			print_path(stack);
		}
		get_path(T->left, data, stack, sum);
		get_path(T->right, data, stack, sum);

		// 回溯到父节点
		if (!stack.empty())
		{
			stack.pop();
			sum -= T->data;
		}
	}
}

// test for `build_silbing_child_list'
void test1()
{
	TreeNode node[MAX_NODE];
	int degree[MAX_NODE] = { 4, 0, 2, 0, 3, 1, 0, 0, 0, 3, 0, 0, 0, 0 };
	int i;

	for (i = 0; i < MAX_NODE; i++)
		node[i] = create_tree_node(i + 1);

	build_sibling_child_list(node, degree, MAX_NODE);
	print_tree(node, MAX_NODE);

	for (i = 0; i < MAX_NODE; i++)
		free(node[i]);
}

// test for `is_bstree' & `get_level'
void test2()
{
	int pre1[] = { 27, 14, 9, 18, 25, 38, 34, 42, 50, 51 };
	int in1[] = { 9, 14, 18, 25, 27, 34, 38, 50, 42, 51 };
	BSTree T1 = build_tree(pre1, 0, _countof(pre1) - 1,
		in1, 0, _countof(in1) - 1);

	int pre2[] = { 27, 14, 9, 18, 25, 38, 34, 42, 51 };
	int in2[] = { 9, 14, 18, 25, 27, 34, 38, 42, 51 };
	BSTree T2 = build_tree(pre2, 0, _countof(pre2) - 1,
		in2, 0, _countof(in2) - 1);

	int pre3[] = { 27, 14, 9, 18, 25, 38, 34, 42, 51, 50 };
	int in3[] = { 9, 14, 18, 25, 27, 34, 38, 42, 50, 51 };
	BSTree T3 = build_tree(pre3, 0, _countof(pre3) - 1,
		in3, 0, _countof(in3) - 1);


	printf("T1 is bstree: %s\n", is_bstree(T1) ? "true" : "false");
	printf("T2 is bstree: %s\n", is_bstree(T2) ? "true" : "false");
	printf("T3 is bstree: %s\n", is_bstree(T3) ? "true" : "false");
	
	for (int i = 0; i < _countof(pre3);i++)
		printf("Level of [%2d] in T3: %d\n", pre3[i], get_level(T3, pre3[i]));
		
	printf("Level of [%2d] in T3: %d\n", 100, get_level(T3, 100));

	destroy_tree(T1);
	destroy_tree(T2);
}

// test for `print_keys'
void test3()
{
	int pre[] = { 27, 14, 9, 18, 25, 38, 34, 42, 50, 51 };
	int in[] = { 9, 14, 18, 25, 27, 34, 38, 50, 42, 51 };
	BSTree T = build_tree(pre, 0, _countof(pre) - 1,
		in, 0, _countof(in) - 1);

	print_keys(T, 25);
	destroy_tree(T);
}

// test for `is_avltree'
void test4()
{
	int height;
	bool balanced;
	int pre1[] = { 27, 14, 9, 18, 25, 26, 38, 34, 42, 50, 51 };
	int in1[] = { 9, 14, 18, 25, 26, 27, 34, 38, 50, 42, 51 };
	BSTree T1 = build_tree(pre1, 0, _countof(pre1) - 1,
		in1, 0, _countof(in1) - 1);

	is_avltree(T1, balanced, height);
	printf("T1 balanced: %s, height: %d\n",
		balanced ? "true" : "false", height);
	
	int pre2[] = { 27, 14, 9, 18, 25, 38, 34, 42, 51 };
	int in2[] = { 9, 14, 18, 25, 27, 34, 38, 42, 51 };
	BSTree T2 = build_tree(pre2, 0, _countof(pre2) - 1,
		in2, 0, _countof(in2) - 1);

	is_avltree(T2, balanced, height);
	printf("T2 balanced: %s, height: %d\n",
		balanced ? "true" : "false", height);
	
	destroy_tree(T1);
	destroy_tree(T2);
}

void test5()
{
	//int pre[] = { 10, 5, 4, 7, 12 };
	//int in[] = { 4, 5, 7, 10, 12 };
	int pre[] = { 10, 5, 1, 3, 20, 18, 7, 15, 12, 8, 7, 4 };
	int in[] = { 20, 3, 18, 1, 5, 15, 7, 10, 8, 7, 12, 4 };
	BinTree T = build_tree(pre, 0, _countof(pre) - 1, in, 0, _countof(in) - 1);
	stack<BinTree> stack;
	int sum = 0;
	//get_path(T, 22, stack, sum);
	get_path(T, 37, stack, sum);
	destroy_tree(T);
}

int main()
{
	test5();
}