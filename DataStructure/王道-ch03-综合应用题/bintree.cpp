#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

BinTree build_tree(int pre[], int pre_from, int pre_to,
	int in[], int in_from, int in_to)
{
	BinTree root;
	int i, shift;
	// 根节点 pre[pre_from]
	root = (BinTree)malloc(sizeof(struct _BinTree));
	root->data = pre[pre_from];

	// 在中序序列中找到根节点 pre[pre_from]
	for (i = in_from; i <= in_to; i++)
	{
		if (in[i] == pre[pre_from])
			break;
	}
	if (i > in_to) // not found
		return NULL;

	shift = i - in_from;
	root->left = build_tree(pre, pre_from + 1, pre_from + shift,
		in, in_from, i - 1);
	root->right = build_tree(pre, pre_from + shift + 1, pre_to,
		in, i + 1, in_to);

	return root;
}

void pre_order(BinTree T)
{
	if (T)
	{
		printf("%d ", T->data);
		pre_order(T->left);
		pre_order(T->right);
	}
}

void in_order(BinTree T)
{
	if (T)
	{
		in_order(T->left);
		printf("%d ", T->data);
		in_order(T->right);
	}
}

void post_order(BinTree T)
{
	if (T)
	{
		post_order(T->left);
		post_order(T->right);
		printf("%d ", T->data);
	}
}

void destroy_tree(BinTree T)
{
	if (T)
	{
		destroy_tree(T->left);
		destroy_tree(T->right);
		free(T);
	}
}

