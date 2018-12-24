#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TreeNode create_tree_node(int data)
{
	TreeNode node;
	node = (TreeNode)malloc(sizeof(struct _TreeNode));
	node->data = data;
	node->child = node->sibling = NULL;
	return node;
}

void print_tree(TreeNode node[], int n)
{
	TreeNode p;
	int i;

	for (i = 0; i < n; i++)
	{
		printf("\n[%d] ", node[i]->data);
		for (p = node[i]->child; p; p = p->sibling)
			printf("%d ", p->data);
	}
}
