#define  _CRT_SECURE_NO_WARNINGS
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stack>
#include <queue>
#include <string>
#include <stdio.h>
#include "priorityqueue.h"

#define MAKE_STRING(s,c) s[0] = c; s[1] = 0
#define BUFSIZE 4

typedef class HuffmanTree *PHuffmanTree;

class HuffmanTree
{
private:
	char mElement[BUFSIZE];
	double mWeight;
	HuffmanTree **mLeaves;
	HuffmanTree *mParent;
	HuffmanTree *mLeft;
	HuffmanTree *mRight;
public:
	HuffmanTree();
	HuffmanTree(char Element, double Weight);
	HuffmanTree *Build(char *Elements, double *Weights, int ElementsNum, PHuffmanTree **Leaves);
	~HuffmanTree();
	char *GetElement();
	double GetWeight();
	std::string EnCode();
	std::queue<char> Decode(std::queue<char> &Sequence);
	void LayerWalker();
};

///////////////////////////////////////////////////////////////

int compare(void *x, void *y)
{
	HuffmanTree *a = (HuffmanTree*)x;
	HuffmanTree *b = (HuffmanTree*)y;
	if (a->GetWeight() == b->GetWeight())
		return 0;
	else if (a->GetWeight() > b->GetWeight())
		return 1;
	else
		return -1;
}

HuffmanTree::HuffmanTree()
{
	mLeaves = NULL;
	mParent = NULL;
	mLeft = mRight = NULL;
}

HuffmanTree::HuffmanTree(char Element, double Weight)
{
	mLeaves = NULL;
	mParent = NULL;
	mLeft = mRight = NULL;
	MAKE_STRING(mElement, Element);
	mWeight = Weight;
}

HuffmanTree::~HuffmanTree()
{
	//std::cout << "delete " << mElement << std::endl;
	if (mLeaves != NULL) delete mLeaves;
	if (mLeft != NULL) delete mLeft;
	if (mRight != NULL) delete mRight;
}

char* HuffmanTree::GetElement()
{
	return mElement;
}

double HuffmanTree::GetWeight()
{
	return mWeight;
}

/**
 * @return 树的根节点
 */
HuffmanTree *HuffmanTree::Build(char *Elements, double *Weights, int ElementsNum, PHuffmanTree **Leaves)
{
	int i;

	// 创建叶子节点
	mLeaves = new HuffmanTree*[ElementsNum];
	for (i = 0; i < ElementsNum; i++)
	{
		mLeaves[i] = new HuffmanTree;
		MAKE_STRING(mLeaves[i]->mElement, Elements[i]);
		mLeaves[i]->mWeight = Weights[i];
	}

	// 将叶子节点堆序化
	HuffmanTree *MinData = new HuffmanTree(0, -1);
	PriorityQueue<HuffmanTree*, compare> Heap(mLeaves, ElementsNum, MinData);

	// 构建 Huffman 树
	i = 1;
	while (Heap.GetSize() > 1)
	{
		HuffmanTree *Temp = new HuffmanTree;
		sprintf(Temp->mElement, "T%d", i++);
		Temp->mParent = NULL;
		Temp->mLeft = Heap.DeleteMin();
		Temp->mLeft->mParent = Temp;
		if (!Heap.IsEmpty())
		{
			Temp->mRight = Heap.DeleteMin();
			Temp->mRight->mParent = Temp;
			Temp->mWeight = Temp->mLeft->mWeight + Temp->mRight->mWeight;
		}
		else
		{
			Temp->mRight = NULL;
			Temp->mWeight = Temp->mLeft->mWeight;
		}
		Heap.Insert(Temp);
	}

	*Leaves = mLeaves;
	return Heap.FindMin();
}

/**
 * @breif 该函数只允许对叶子节点调用
 */
std::string HuffmanTree::EnCode()
{
	std::string code;
	std::stack<char> s;
	HuffmanTree *p;

	if (this->mLeft != NULL && this->mRight != NULL)
	{
		std::cerr << "EnCode() must be called by leaf" << std::endl;
		return code;
	}
	
	p = this;
	while (p && p->mParent)
	{
		if (p->mParent->mLeft == p)
			s.push(0);
		else if (p->mParent->mRight == p)
			s.push(1);
		p = p->mParent;
	}
	while (!s.empty())
	{
		code.append(std::to_string(s.top()));
		s.pop();
	}

	return code;
}

/**
 * @breif 该函数只允许对根节点调用
 */
std::queue<char> HuffmanTree::Decode(std::queue<char> &Sequence)
{
	std::queue<char> Code;
	HuffmanTree *p = NULL, *Child = NULL;

	if (this->mParent != NULL)
	{
		std::cerr << "DeCode() must be called by root." << std::endl;
		return Code;
	}

	// 从根节点开始, 若从待解码序列中读入 0 则进入左子树; 读入 1 则进入右子树,
	// 直到找到叶子节点, 从而完成一个字符的解码.
	while (!Sequence.empty())
	{
		p = this;
		while (p && p->mLeft && p->mRight && !Sequence.empty())
		{
			if (Sequence.front() == '0')
				p = p->mLeft;
			else if (Sequence.front() == '1')
				p = p->mRight;
			Sequence.pop();
		}
		Code.push(p->GetElement()[0]);
	}
	return Code;
}

void HuffmanTree::LayerWalker()
{
	std::cout << std::endl << "Layer walker:" << std::endl;

	std::queue<HuffmanTree*> q;
	q.push(this);
	while (!q.empty())
	{
		HuffmanTree *T = q.front();
		q.pop();
		if (T != NULL)
		{
			std::cout << T->mElement << "-";
			q.push(T->mLeft);
			q.push(T->mRight);
		}
	}
	std::cout << "\b " << std::endl;
}

#endif // HUFFMAN_H
