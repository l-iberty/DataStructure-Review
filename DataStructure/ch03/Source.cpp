#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (((a)>(b))?(a):(b))

typedef struct _BSTree *BSTree;
typedef struct _Queue *Queue;

struct _BSTree {
	int data;
	BSTree left;
	BSTree right;
};

struct _Queue {
	BSTree data;
	Queue next;
};

Queue CreateQueue()
{
	Queue queue = (Queue)malloc(sizeof(struct _Queue));
	queue->next = NULL;

	return queue;
}

void Enqueue(Queue queue, BSTree x)
{
	Queue node, p;
	node = (Queue)malloc(sizeof(struct _Queue));
	node->data = x;
	node->next = NULL;

	for (p = queue; p->next; p = p->next);

	p->next = node;
}

BSTree Dequeue(Queue queue)
{
	Queue p = queue->next;
	if (p == NULL)
	{
		return NULL;
	}

	BSTree x = p->data;
	queue->next = queue->next->next;
	free(p);
	return x;
}

int isEmptyQueue(Queue queue)
{
	return (queue->next == NULL ? 1 : 0);
}

void FreeQueue(Queue queue)
{
	Queue current, next;
	current = queue;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

////////////////////////////////////////////////////////////

BSTree Insert(BSTree T, int x)
{
	if (T == NULL)
	{
		T = (BSTree)malloc(sizeof(struct _BSTree));
		T->data = x;
		T->left = NULL;
		T->right = NULL;
	}
	else if (x < T->data)
	{
		T->left = Insert(T->left, x);
	}
	else if (x > T->data)
	{
		T->right = Insert(T->right, x);
	}
	// else x is in the tree already; we'll do nothing.

	return T;
}

BSTree Find(BSTree T, int x)
{
	if (T == NULL)
		return NULL;

	if (x == T->data)
		return T;
	else if (x < T->data)
		return Find(T->left, x);
	else
		return Find(T->right, x);
}

BSTree FindMax(BSTree T)
{
	if (T == NULL)
		return NULL;

	while (T->right != NULL)
	{
		T = T->right;
	}
	return T;
}

BSTree FindMin(BSTree T)
{
	if (T == NULL)
		return NULL;

	if (T->left == NULL)
		return T;

	return FindMin(T->left);
}

BSTree Delete(BSTree T, int x)
{
	BSTree Tmp;

	if (T == NULL)
		return NULL;
	
	if (x < T->data)
		T->left = Delete(T->left, x);
	else if (x > T->data)
		T->right = Delete(T->right, x);
	else // Find element to be deleted
	{
		if (T->left && T->right)
		{
			// Replace with smallest in the right tree
			T->data = FindMin(T->right)->data;
			T->right = Delete(T->right, T->data);
		}
		else
		{
			Tmp = T;
			if (T->left == NULL)
				T = T->right;
			else if (T->right == NULL)
				T = T->left;
			free(Tmp);
		}
	}
	return T;
}

void PreOrder(BSTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreOrder(T->left);
		PreOrder(T->right);
	}
}

void InOrder(BSTree T)
{
	if (T != NULL)
	{
		InOrder(T->left);
		printf("%d ", T->data);
		InOrder(T->right);
	}
}

void PostOrder(BSTree T)
{
	if (T != NULL)
	{
		PostOrder(T->left);
		PostOrder(T->right);
		printf("%d ", T->data);
	}
}

void LayerOrder(BSTree T)
{
	Queue queue = CreateQueue();
	Enqueue(queue, T);
	while (!isEmptyQueue(queue))
	{
		BSTree x = Dequeue(queue);
		printf("%d ", x->data);
		if (x->left)
		{
			Enqueue(queue, x->left);
		}
		if (x->right)
		{
			Enqueue(queue, x->right);
		}
	}
	FreeQueue(queue);
}

/**
 * 根据前序序列和中序序列构造二叉树
 *
 * @param pre[] 前序序列
 * @param in[]  后续序列
 * 
 * 使用 pre[preFrom] ~ pre[preTo] 和
 * in[inFrom] ~ in[inTo] 中的元素构造二叉树.
 */
BSTree BuildBiTree(int pre[], int preFrom, int preTo,
	int in[], int inFrom, int inTo)
{
	int i, leftLen;
	BSTree root = NULL;

	// 前序序列 pre[] 的第一个元素是根节点
	root = (BSTree)malloc(sizeof(struct _BSTree));
	root->data = pre[preFrom];

	// 在中序序列 in[] 中找到根节点
	for (i = inFrom; i <= inTo; i++)
	{
		if (root->data == in[i])
			break; // Found
	}
	if (i > inTo) // Not found
		return NULL;
	
	// i = 根节点在中序序列中的位置.
	// 在中序序列中, i 左侧的元素都属于根节点的左子树;
	// i 右侧的元素都属于根节点的右子树.

	leftLen = i - inFrom; // 根节点的左子树中有几个元素?

	// 递归地构造左、右子树

	root->left = BuildBiTree(pre, preFrom + 1, preFrom + leftLen, 
		in, inFrom, i - 1);

	root->right = BuildBiTree(pre, preFrom + leftLen + 1, preTo,
		in, i + 1, inTo);

	return root;
}

void ExchangeLR(BSTree T)
{
	BSTree temp;
	if (T != NULL)
	{
		temp = T->left;
		T->left = T->right;
		T->right = temp;
		
		ExchangeLR(T->left);
		ExchangeLR(T->right);
	}
}

int CountLeaves(BSTree T)
{
	int totalLeaves = 0;

	if (T != NULL)
	{
		totalLeaves = CountLeaves(T->left) + CountLeaves(T->right);
		if (T->left == NULL && T->right == NULL)
			totalLeaves += 1;
	}

	return totalLeaves;
}

int Depth(BSTree T)
{
	if (T != NULL)
	{
		if (T->left == NULL && T->right == NULL)
			return 0;

		return max(Depth(T->left), Depth(T->right)) + 1;
	}
	return 0;
}

int CountNodes(BSTree T)
{
	if (T != NULL)
	{
		return (CountNodes(T->left) + CountNodes(T->right)) + 1;
	}
	return 0;
}

/**
 * 打印二叉树中的属于区间 [a, b] 的元素
 */
void PrintRange(BSTree T, int a, int b)
{
	if (T != NULL)
	{
		if (T->data >= a && T->data <= b)
			printf("[%d] ", T->data);
		PrintRange(T->left, a, b);
		PrintRange(T->right, a, b);
	}
}

void FreeBSTree(BSTree T)
{
	if (T != NULL)
	{
		FreeBSTree(T->left);
		FreeBSTree(T->right);
		free(T);
	}
}

int main()
{
	BSTree T = NULL;
	int i;
	int s[10] = { 5, 7, 4, 6, 8, 10, 1, 9, 2, 3 };
	
	for (i = 0; i < 10; i++)
		T = Insert(T, s[i]);
//
//           5
//         /   \
//        4     7
//       /     / \
//      1     6   8
//       \         \
//        2         10
//         \        /
//          3      9
//

	PreOrder(T);
	printf("\n");
	
	InOrder(T);
	printf("\n");

	PostOrder(T);
	printf("\n");
	
	LayerOrder(T);
	printf("\n");

	printf("Min: %d, Max: %d\n", FindMin(T)->data, FindMax(T)->data);

	printf("[2~9]: ");
	PrintRange(T, 2, 9);
	printf("\n");

	T = Delete(T, 7);
	printf("Delete 7:\n");
	LayerOrder(T);
	printf("\n");

	FreeBSTree(T);

	BSTree root = NULL;
	int pre[11] = { 1, 5, 8, 2, 4, 3, 7, 10, 15, 20, 9 };
	int in[11] = { 8, 5, 4, 2, 1, 10, 7, 20, 15, 3, 9 };
//
//				    1
//                /   \
//              5       3
//             / \     / \
//            8   2   7   9
//               /   / \
//              4   10 15
//                     /
//                    20
	
	//int pre[10] = { 5, 4, 1, 2, 3, 7, 6, 8, 10, 9 };
	//int in[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	root = BuildBiTree(pre, 0, 10, in, 0, 10);
	printf("\n$ ");
	PostOrder(root);
	ExchangeLR(root);
	printf("\n$ ");
	PreOrder(root);
	printf("\n$ ");
	InOrder(root);
	printf("\n");
	printf("Leaves : %d\n", CountLeaves(root));
	printf("Depth : %d\n", Depth(root));
	printf("Nodes : %d\n", CountNodes(root));
//
//				1
//            /   \
//          3       5
//         / \     / \
//        9   7   2   8
//           / \   \
//          15 10   4
//			  \
//            20

	FreeBSTree(root);
}