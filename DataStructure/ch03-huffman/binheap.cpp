#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "binheap.h"

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	ElementType MinData;

	MAKE_MINDATA(MinData);

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	H->Elements = (ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MinData;

	return H;
}

/**
 * @return
 * 0 (e1 == e2)
 * -1 (e2 < e2)
 * 1 (e1 > e2)
 */
static int Compare(ElementType e1, ElementType e2)
{
	if (e1->Weight == e2->Weight)
		return 0;
	else if (e1->Weight < e2->Weight)
		return -1;
	else
		return 1;
}
/**
 * Elements[0] Ϊ MINDATA
 * Ԫ���±� 1 ~ N
 * -- ��ͬ
 */
static void PercolateDown(ElementType *Elements, int N, int Index)
{
	int i, Child;
	ElementType Tmp;

	// Ѱ�ҿ��Է��� Tmp ��λ�� i
	Tmp = Elements[Index];
	for (i = Index; i * 2 <= N; i = Child) // ָ�� i ��ʼ�� Index, ���Ž�С���ӽڵ��ƶ�
	{
		// Find smaller child.
		Child = 2 * i; // left child
		if (Child < N &&
			Compare(Elements[Child + 1], Elements[Child]) < 0)
		{
			Child++; // right child
		}

		if (Compare(Tmp, Elements[Child]) > 0)
		{
			// ����� Tmp ���� i �ڵ㴦, ���ƻ���������, ��Ҫ�� i �ڵ��С�������Ƶ� i ��.
			Elements[i] = Elements[Child];
		}
		else
		{
			// ���Խ� Tmp ���� i �ڵ㴦
			break;
		}
	}
	Elements[i] = Tmp;
}

static void PercolateUp(ElementType *Elements, int N, int Index)
{
	int i;
	ElementType Tmp;

	Tmp = Elements[Index];
	for (i = Index; i > 0; i /= 2) // ָ�� i ��ʼ�� Index, ���Ÿ��ڵ��ƶ�
	{
		if (Compare(Tmp, Elements[i / 2]) < 0)
			Elements[i] = Elements[i / 2];
		else
			break;
	}
	Elements[i] = Tmp;
}

// O(N)
PriorityQueue BuildHeap(ElementType *Elements, int N)
{
	PriorityQueue H;
	int i;

	for (i = N / 2; i > 0; i--)
	{
		PercolateDown(Elements, N, i);
	}

	H = Initialize(N);
	memcpy(H->Elements, Elements, (N + 1) * sizeof(ElementType));
	H->Size = N;

	return H;
}

void Destory(PriorityQueue H)
{
	free(H->Elements);
	free(H);
}

// O(log N)
void Insert(ElementType x, PriorityQueue H)
{
	int i;

	if (IsFull(H))
	{
		printf("Priority queue is full\n");
		return;
	}

	i = ++H->Size;
	while (Compare(x, H->Elements[i / 2]) < 0)
	{
		H->Elements[i] = H->Elements[i / 2]; // �����ڵ�����
		i = i / 2; // ָ�� i �򸸽ڵ��ƶ�
	}
	H->Elements[i] = x;
}

// O(log N)
ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;

	if (IsEmpty(H))
	{
		printf("Priority queue is empty\n");
		return H->Elements[0];
	}

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--]; // "Size--" ������ LastElement �븸�ڵ������

	// i ��������� 2i ��, �Ҷ����� 2i+1 ��
	for (i = 1; i * 2 <= H->Size; i = Child)
	{
		// �� Child ָ�����Ҷ����еĽ�С��
		Child = i * 2;
		if (Child < H->Size && // ��ֹ Child+1 Խ��. �����η����ڵ�ǰ�� H->Size Ϊż��ʱ
			Compare(H->Elements[Child + 1], H->Elements[Child]) < 0)
		{
			Child++;
		}

		// �� Child ����.
		// ���� LastElement �븸�ڵ�����߻�����, ��ʱ��� Child �� LastElement
		// �й�ͬ�ĸ��ڵ�, �� Child > LastElement, ��ô�� Child ���ƺ�, ѭ������
		// �� i ָ�� Child ԭ����λ��, LastElement ���ƽ���λ�þͻ��ƻ���������.
		// �� binheap2.vsdx ��ģ�� DeleteMin �ĵ��ü��ɷ��ָ�����.
		if (Compare(H->Elements[Child], LastElement) < 0)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}

	H->Elements[i] = LastElement;
	return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
	if (IsEmpty(H))
	{
		printf("Priority queue is empty\n");
		return H->Elements[0];
	}
	return H->Elements[1];
}

void DecreaseKey(PriorityQueue H, int Index, int Delta)
{
	H->Elements[Index] -= Delta;
	PercolateUp(H->Elements, H->Size, Index);
}

void IncreaseKey(PriorityQueue H, int Index, int Delta)
{
	H->Elements[Index] += Delta;
	PercolateDown(H->Elements, H->Size, Index);
}

void UpdataKey(PriorityQueue H, int Index, ElementType NewValue)
{
	ElementType OldValue;
	
	OldValue = H->Elements[Index];
	H->Elements[Index] = NewValue;

	if (Compare(OldValue, NewValue) > 0)
		PercolateUp(H->Elements, H->Size, Index);
	else
		PercolateDown(H->Elements, H->Size, Index);
}

ElementType Delete(PriorityQueue H, int Index)
{
	ElementType MinElement;

	MinElement = FindMin(H);
	UpdataKey(H, Index, MinElement - 1);
	return DeleteMin(H);
}

int IsEmpty(PriorityQueue H)
{
	return (H->Size == 0);
}

int IsFull(PriorityQueue H)
{
	return (H->Size == H->Capacity);
}

