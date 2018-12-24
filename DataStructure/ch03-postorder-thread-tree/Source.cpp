// 后序线索二叉树, 需要增加 Parent 指针
// 遍历存在BUG

#include <stdio.h>
#include <stdlib.h>

#define TreeNode(x) (x->Data)

typedef struct _List *List;
typedef struct _BinTree *BinTree;

struct _List {
	BinTree Data;
	List Next;
};

struct _BinTree {
	int Data;
	BinTree Parent;
	BinTree Left;
	BinTree Right;
	char LTag; // 0 - Left指向左子树; 1 - Left指向前驱(predecessor)
	char RTag; // 0 - Right指向右子树; 1 - Right指向后继(successor)
};


List CreateList()
{
	List L = (List)malloc(sizeof(struct _List));
	L->Data = NULL;
	L->Next = NULL;
	return L;
}

void PushBack(List L, BinTree Data)
{
	List p, node;

	for (p = L; p->Next; p = p->Next);

	node = (List)malloc(sizeof(struct _List));
	node->Data = Data;
	node->Next = NULL;
	p->Next = node;
}

///////////////////////////////////////////////////////////////////

/**
* 根据前序序列和中序序列构造二叉树
*
* @param pre[] 前序序列
* @param in[]  后续序列
*
* 使用 pre[preFrom] ~ pre[preTo] 和
* in[inFrom] ~ in[inTo] 中的元素构造二叉树.
*/
BinTree BuildBinTree(int pre[], int preFrom, int preTo,
	int in[], int inFrom, int inTo)
{
	int i, LeftLen;
	BinTree root = NULL;

	// 前序序列 pre[] 的第一个元素是根节点
	root = (BinTree)malloc(sizeof(struct _BinTree));
	root->Data = pre[preFrom];
	root->LTag = root->RTag = 0;

	// 在前序序列 in[] 中找到根节点
	for (i = inFrom; i <= inTo; i++)
	{
		if (root->Data == in[i])
			break; // Found
	}
	if (i > inTo) // Not found
		return NULL;

	// i = 根节点在中序序列中的位置.
	// 在中序序列中, i 左侧的元素都属于根节点的左子树;
	// i 右侧的元素都属于根节点的右子树.

	LeftLen = i - inFrom; // 根节点的左子树中有几个元素?

	// 递归地构造左、右子树

	root->Left = BuildBinTree(pre, preFrom + 1, preFrom + LeftLen,
		in, inFrom, i - 1);

	root->Right = BuildBinTree(pre, preFrom + LeftLen + 1, preTo,
		in, i + 1, inTo);

	root->Parent = NULL;

	if (root != NULL)
	{
		if (root->Left != NULL)
			root->Left->Parent = root;
		if (root->Right != NULL)
			root->Right->Parent = root;
	}

	return root;
}

void PostOrder(BinTree T, List list)
{
	if (T != NULL)
	{
		PostOrder(T->Left, list);
		PostOrder(T->Right, list);
		PushBack(list, T);
	}
}

BinTree StartNode(BinTree T)
{
	BinTree p = NULL;

	if (T->Parent != NULL) // T不是根节点
	{
		if (T == T->Parent->Left)
		{
			// T是其父节点的左儿子, 则从T的父节点的右儿子开始, 找到"最左"的节点
			p = T->Parent->Right;
			while (p->LTag == 0 && p->Left != NULL)
				p = p->Left;
		}
		else if (T == T->Parent->Right)
		{
			// T是其父节点的右儿子, 则T的父节点就是下一个被访问的节点
			p = T->Parent;
		}
	}
	else
	{
		// T 是根节点, 找到"最左"的节点
		p = T;
		while (p->LTag == 0 && p->Left != NULL)
			p = p->Left;
	}
	return p;
}

void PostOrderTraverse(BinTree T)
{
	BinTree p;

	p = T;
	while (p != NULL)
	{
		// 找到遍历的起点
		p = StartNode(p);
		printf("%d ", p->Data);
		if (p == T)
			break; // 根节点已被访问, 遍历结束

		// 使用后继线索进行遍历
		while (p->RTag == 1 && p->Right != NULL)
		{
			p = p->Right; // 取出 p 的后继
			printf("%d ", p->Data);
		}
	}
	printf("\n");
}

void MakePostOrderThread(BinTree T)
{
	List list;
	List p, prev;

	list = CreateList();
	PostOrder(T, list);

	p = list->Next;
	while (p && p->Next)
	{
		prev = p;
		p = p->Next;

		// 设置 p 的前驱为 prev
		if (TreeNode(p)->Left == NULL)
		{
			TreeNode(p)->Left = TreeNode(prev);
			TreeNode(p)->LTag = 1;
		}
		else
		{
			TreeNode(p)->LTag = 0;
		}

		// 设置 prev 的后继为 p
		if (TreeNode(prev)->Right == NULL)
		{
			TreeNode(prev)->Right = TreeNode(p);
			TreeNode(prev)->RTag = 1;
		}
		else
		{
			TreeNode(prev)->RTag = 0;
		}
	}
}

int main()
{
	BinTree T;
	//int pre[] = { 7, 4, 2, 1, 3, 6, 5, 13, 11, 9, 8, 10, 12, 15, 14, 16 };
	//int in[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	int pre[] = { 5, 1, 3, 9, 7 };
	int in[] = { 1, 3, 5, 7, 9 };

	T = BuildBinTree(pre, 0, _countof(pre) - 1, in, 0, _countof(in) - 1);
	MakePostOrderThread(T);
	PostOrderTraverse(T);
}