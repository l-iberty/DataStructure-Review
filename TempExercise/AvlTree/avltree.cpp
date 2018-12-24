#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"


AvlTree avl_insert(AvlTree T, int data)
{
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlTree_t));
		T->data = data;
		T->left = T->right = NULL;
	}
	else if (data < T->data)
	{
		T->left = avl_insert(T->left, data);
		if (height(T->left) - height(T->right) == 2)
		{
			if (data < T->left->data)
				T = single_rotate_left(T);
			else
				T = double_rotate_left(T);
		}
	}
	else if (data > T->data)
	{
		T->right = avl_insert(T->right, data);
		if (height(T->right) - height(T->left) == 2)
		{
			if (data > T->right->data)
				T = single_rotate_right(T);
			else
				T = double_rotate_right(T);
		}
	}
		
	T->height = MAX(height(T->left), height(T->right)) + 1;
	return T;
}

AvlTree avl_delete(AvlTree T, int data)
// 未实现平衡操作
{
	AvlTree tmp;

	if (T == NULL)
		return NULL;

	if (data < T->data)
	{
		T->left = avl_delete(T->left, data);
	}
	else if (data > T->data)
	{
		T->right = avl_delete(T->right, data);
	}
	else
	{
		if (T->left && T->right)
		{
			tmp = avl_find_min(T->right);
			T->data = tmp->data;
			T->right = avl_delete(T->right, tmp->data);
		}
		else
		{
			tmp = T;
			if (T->left == NULL)
				T = T->right;
			else
				T = T->left;
			free(tmp);
		}
	}
	
	return T;
}

AvlTree avl_find_max(AvlTree T)
{
	if (T == NULL)
		return NULL;
	if (T->right == NULL)
		return T;
	return avl_find_max(T->right);
}

AvlTree avl_find_min(AvlTree T)
{
	while (T != NULL && T->left != NULL)
		T = T->left;
	return T;
}

// 被插入到左子树"外面"
AvlTree single_rotate_left(AvlTree K)
{
	AvlTree K1;

	K1 = K->left;
	K->left = K1->right;
	K1->right = K;

	K->height = MAX(height(K->left), height(K->right)) + 1;
	K1->height = MAX(height(K1->left), height(K1->right)) + 1;
	return K1;
}

// 被插入到右子树"外面"
AvlTree single_rotate_right(AvlTree K)
{
	AvlTree K1;

	K1 = K->right;
	K->right = K1->left;
	K1->left = K;
	
	K->height = MAX(height(K->left), height(K->right)) + 1;
	K1->height = MAX(height(K1->left), height(K1->right)) + 1;
	return K1;
}

// 被插入到左子树"里面"
AvlTree double_rotate_left(AvlTree K)
{
	K->left = single_rotate_right(K->left);
	return single_rotate_left(K);
}

// 被插入到右子树"里面"
AvlTree double_rotate_right(AvlTree K)
{
	K->right = single_rotate_left(K->right);
	return single_rotate_right(K);
}

int height(AvlTree T)
{
	if (T == NULL)
		return (-1);

	return T->height;
}

void pre_order(AvlTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		pre_order(T->left);
		pre_order(T->right);
	}
}

void in_order(AvlTree T)
{
	if (T != NULL)
	{
		in_order(T->left);
		printf("%d ", T->data);
		in_order(T->right);
	}
}

void destroy(AvlTree T)
{
	if (T != NULL)
	{
		destroy(T->left);
		destroy(T->right);
		free(T);
	}
}
