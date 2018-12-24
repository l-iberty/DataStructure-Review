#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include "huffman.h"
#include "binheap.h"

/**
 * @param Weight ÿ�� Elements[i] ��Ӧ��Ȩ��ֵ
 * @param LeafList �������, �����߿��Ի��ָ��Ҷ�ӽڵ��ָ������
 */
HuffmanTree CreateHuffmanTree(char *Elements, double *Weights, int ElementsNum, HuffmanTree **LeafList)
{
	HuffmanTree T, MinData, Tmp;
	HuffmanTree *Leaves;
	PriorityQueue H;
	int i;

	// ����Ҷ�ӽڵ�
	Leaves = (HuffmanTree*)malloc((ElementsNum + 1)*sizeof(HuffmanTree));
	for (i = 1; i <= ElementsNum; i++)
	{
		Leaves[i] = (HuffmanTree)malloc(sizeof(struct _HuffmanTree));
		MAKE_STRING(Leaves[i]->Element, Elements[i - 1]);
		Leaves[i]->Weight = Weights[i - 1];
		Leaves[i]->Left = Leaves[i]->Right = NULL;
	}
	
	MAKE_MINDATA(MinData);
	Leaves[0] = MinData;

	// ��Ҷ�ӽڵ����
	H = BuildHeap(Leaves, ElementsNum);

	// ��ʼ���� Huffman ��
	i = 1;
	while (H->Size > 1)
	{
		Tmp = (HuffmanTree)malloc(sizeof(struct _HuffmanTree));
		Tmp->Parent = NULL;
		sprintf(Tmp->Element, "T%d", i++);
		Tmp->Left = DeleteMin(H);
		Tmp->Left->Parent = Tmp;
		if (!IsEmpty(H))
		{
			Tmp->Right = DeleteMin(H);
			Tmp->Right->Parent = Tmp;
			Tmp->Weight = Tmp->Left->Weight + Tmp->Right->Weight;
		}
		else
		{
			Tmp->Right = NULL;
			Tmp->Weight = Tmp->Left->Weight;
		}

		Insert(Tmp, H);
	}

	T = H->Elements[1]; // ��ȡ���ĸ��ڵ�
	Destory(H);

	*LeafList = Leaves;
	return T;
}

/**
 * @brief ��ȡҶ�ӽڵ� K �� Huffman ����
 */
void GetCode(HuffmanTree K, std::stack<char> &code)
{
	for (; K && K->Parent; K = K->Parent)
	{
		if (K == K->Parent->Left) // K �Ǹ��ڵ�������
			code.push(0);
		else if (K == K->Parent->Right) // K �Ǹ��ڵ���Ҷ���
			code.push(1);
	}
}

void LayerWalker(HuffmanTree T)
{
	std::queue<HuffmanTree> q;
	q.push(T);
	while (!q.empty())
	{
		T = q.front();
		q.pop();
		if (T != NULL)
		{
			printf("%s-", T->Element);
			q.push(T->Left);
			q.push(T->Right);
		}
	}
}

void FreeHuffmanTree(HuffmanTree T)
{
	if (T != NULL)
	{
		FreeHuffmanTree(T->Left);
		FreeHuffmanTree(T->Right);
		free(T);
	}
}
