// ��������������

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
	BinTree Left;
	BinTree Right;
	char LTag; // 0 - Leftָ��������; 1 - Leftָ��ǰ��(predecessor)
	char RTag; // 0 - Rightָ��������; 1 - Rightָ����(successor)
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
* ����ǰ�����к��������й��������
*
* @param pre[] ǰ������
* @param in[]  ��������
*
* ʹ�� pre[preFrom] ~ pre[preTo] ��
* in[inFrom] ~ in[inTo] �е�Ԫ�ع��������.
*/
BinTree BuildBinTree(int pre[], int preFrom, int preTo,
	int in[], int inFrom, int inTo)
{
	int i, LeftLen;
	BinTree root = NULL;

	// ǰ������ pre[] �ĵ�һ��Ԫ���Ǹ��ڵ�
	root = (BinTree)malloc(sizeof(struct _BinTree));
	root->Data = pre[preFrom];
	root->LTag = root->RTag = 0;

	// ��ǰ������ in[] ���ҵ����ڵ�
	for (i = inFrom; i <= inTo; i++)
	{
		if (root->Data == in[i])
			break; // Found
	}
	if (i > inTo) // Not found
		return NULL;

	// i = ���ڵ������������е�λ��.
	// ������������, i ����Ԫ�ض����ڸ��ڵ��������;
	// i �Ҳ��Ԫ�ض����ڸ��ڵ��������.

	LeftLen = i - inFrom; // ���ڵ�����������м���Ԫ��?

	// �ݹ�ع�����������

	root->Left = BuildBinTree(pre, preFrom + 1, preFrom + LeftLen,
		in, inFrom, i - 1);

	root->Right = BuildBinTree(pre, preFrom + LeftLen + 1, preTo,
		in, i + 1, inTo);

	return root;
}

void InOrder(BinTree T, List list)
{
	if (T != NULL)
	{
		InOrder(T->Left, list);
		PushBack(list, T);
		InOrder(T->Right, list);
	}
}

inline BinTree StartNode(BinTree T)
{
	while (T->LTag == 0 && T->Left != NULL)
		T = T->Left;
	return T;
}

void InOrderTraverse(BinTree T)
{
	BinTree p;

	p = T;
	while (p != NULL)
	{
		// �ҵ����������
		p = StartNode(p);
		printf("%d ", p->Data);

		// ʹ�ú���������б���
		while (p->RTag == 1 && p->Right != NULL)
		{
			p = p->Right; // ȡ�� p �ĺ��
			printf("%d ", p->Data);
		}

		// ����ʹ�ú������ʱ, �� p ����������ʼ, ����һ��ѭ��������ȷ�����������
		p = p->Right;
	}
	printf("\n");
}

void MakeInOrderThread(BinTree T)
{
	List list;
	List p, prev;

	list = CreateList();
	InOrder(T, list);

	p = list->Next;
	while (p && p->Next)
	{
		prev = p;
		p = p->Next;

		// ���� p ��ǰ��Ϊ prev
		if (TreeNode(p)->Left == NULL)
		{
			TreeNode(p)->Left = TreeNode(prev);
			TreeNode(p)->LTag = 1;
		}
		else
		{
			TreeNode(p)->LTag = 0;
		}

		// ���� prev �ĺ��Ϊ p
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
	MakeInOrderThread(T);
	InOrderTraverse(T);
}