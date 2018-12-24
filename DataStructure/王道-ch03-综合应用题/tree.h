#ifndef TREE_H
#define TREE_H

typedef struct _TreeNode *TreeNode;

struct _TreeNode
{
	int data;
	TreeNode child;
	TreeNode sibling;
};

TreeNode create_tree_node(int data);
void print_tree(TreeNode node[], int n);

#endif // TREE_H
