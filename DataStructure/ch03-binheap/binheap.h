#ifndef BINHEAP_H
#define BINHEAP_H

#define MINDATA -1

typedef int ElementType;

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
