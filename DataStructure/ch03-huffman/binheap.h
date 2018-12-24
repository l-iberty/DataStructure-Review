#ifndef BINHEAP_H
#define BINHEAP_H

#include "huffman.h"

#define MINDATA -1
#define MAKE_MINDATA(x) x = (HuffmanTree)malloc(sizeof(struct _HuffmanTree)); \
	x->Weight = MINDATA; \
	x->Parent = x->Left = x->Right = NULL

typedef HuffmanTree ElementType;

typedef struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
} *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
PriorityQueue BuildHeap(ElementType *Elements, int N);
void Destory(PriorityQueue H);
void Insert(ElementType x, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
void DecreaseKey(PriorityQueue H, int Index, int Delta);
void IncreaseKey(PriorityQueue H, int Index, int Delta);
void UpdataKey(PriorityQueue H, int Index, ElementType NewValue);
ElementType Delete(PriorityQueue H, int Index);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

#endif // BINHEAP_H
