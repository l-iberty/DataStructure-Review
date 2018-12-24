#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include "huffman.h"
#include "binheap.h"

/**
 * @param Weight 每个 Elements[i] 对应的权重值
 * @param LeafList 输出参数, 调用者可以获得指向叶子节点的指针序列
 */
HuffmanTree CreateHuffmanTree(char *Elements, double *Weights, int ElementsNum, HuffmanTree **LeafList)
{
	HuffmanTree T, MinData, Tmp;
	HuffmanTree *Leaves;
	PriorityQueue H;
	int i;

	// 创建叶子节点
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

	// 将叶子节点堆序化
	H = BuildHeap(Leaves, ElementsNum);

	// 开始构建 Huffman 树
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

	T = H->Elements[1]; // 获取树的根节点
	Destory(H);

	*LeafList = Leaves;
	return T;
}

/**
 * @brief 获取叶子节点 K 的 Huffman 编码
 */
void GetCode(HuffmanTree K, std::stack<char> &code)
{
	for (; K && K->Parent; K = K->Parent)
	{
		if (K == K->Parent->Left) // K 是父节点的左儿子
			code.push(0);
		else if (K == K->Parent->Right) // K 是父节点的右儿子
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
