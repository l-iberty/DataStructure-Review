#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "binheap.h"

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	H->Elements = (ElementType*)malloc((MaxElements + 1) * sizeof(ElementType));
	H->Capacity = MaxElements;
	H->Size = 0;
	H->Elements[0] = MINDATA;

	return H;
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
			Elements[Child + 1] < Elements[Child])
		{
			Child++; // right child
		}

		if (Tmp > Elements[Child])
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
		if (Tmp < Elements[i / 2])
			Elements[i] = Elements[i / 2];
		else
			break;
	}
	Elements[i] = Tmp;
}

/**
 * @return
 * (-1) if (e1 < e2>
 * (0)  if (e1 == e2)
 * (1)  if (e1 > e2)
 */
static int Compare(ElementType e1, ElementType e2)
{

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
	while (x < H->Elements[i / 2])
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
			H->Elements[Child] > H->Elements[Child + 1])
		{
			Child++;
		}

		// �� Child ����.
		// ���� LastElement �븸�ڵ�����߻�����, ��ʱ��� Child �� LastElement
		// �й�ͬ�ĸ��ڵ�, �� Child > LastElement, ��ô�� Child ���ƺ�, ѭ������
		// �� i ָ�� Child ԭ����λ��, LastElement ���ƽ���λ�þͻ��ƻ���������.
		// �� binheap2.vsdx ��ģ�� DeleteMin �ĵ��ü��ɷ��ָ�����.
		if (H->Elements[Child] < LastElement)
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

	if (OldValue > NewValue)
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

////////////////////////////////////////////////////////

void Test1()
{
	int i;
	PriorityQueue H;
	ElementType x[11] = { 13, 14, 16, 19, 21, 19, 68, 65, 26, 32, 31 };

	H = Initialize(20);
	for (i = 0; i < 11; i++)
		Insert(x[i], H);

	printf("$ Test1: ");
	while (!IsEmpty(H))
		printf("%d ", DeleteMin(H));

	printf("\n");
	Destory(H);
}

void Test2() // heap sort
// ������:
// 1. ���� BuildHeap() ���ؼ������ж���, ���Ӷ�Ϊ O(N)
// 2. ���� DeleteMin() ���ؼ��ְ��������,
//    ��Ҫ���� O(N) �� DeleteMin(), DeleteMin() �ĸ��Ӷ��� O(log N), ��˸��Ӷ��� O(Nlog N)
//
// ����, T(N) = O(N) + O(Nlog N) = O(Nlog N)
{
#define NUM 16

	PriorityQueue H;
	int i;
	ElementType x[NUM];

	srand((unsigned)time(NULL));
	for (i = 1; i < NUM; i++)
		x[i] = rand() % 200;

	x[0] = MINDATA;
	H = BuildHeap(x, NUM - 1);
	
	printf("$ Test2: ");
	while (!IsEmpty(H))
		printf("%d ", DeleteMin(H));

	printf("\n");
	Destory(H);
}

void Test3()
{
	PriorityQueue H;
	ElementType x[16] = { MINDATA,
		10, 20, 40, 30, 60, 50, 110, 100, 150, 90, 80, 70, 120, 140, 130 };

	H = Initialize(15);
	memcpy(H->Elements, x, sizeof(x));
	H->Size = 15;

	IncreaseKey(H, 2, 200);

	printf("$ Test3: ");
	while (!IsEmpty(H))
		printf("%d ", DeleteMin(H));

	printf("\n");
	Destory(H);

}

void Test4()
{
	PriorityQueue H;
	ElementType x[16] = { MINDATA,
		10, 20, 40, 30, 60, 50, 110, 100, 150, 90, 80, 70, 120, 140, 130 };

	H = Initialize(15);
	memcpy(H->Elements, x, sizeof(x));
	H->Size = 15;

	Delete(H, 7);

	printf("$ Test4: ");
	while (!IsEmpty(H))
		printf("%d ", DeleteMin(H));

	printf("\n");
	Destory(H);
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
}