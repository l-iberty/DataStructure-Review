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
 * Elements[0] 为 MINDATA
 * 元素下标 1 ~ N
 * -- 下同
 */
static void PercolateDown(ElementType *Elements, int N, int Index)
{
	int i, Child;
	ElementType Tmp;

	// 寻找可以放置 Tmp 的位置 i
	Tmp = Elements[Index];
	for (i = Index; i * 2 <= N; i = Child) // 指针 i 起始于 Index, 向着较小的子节点移动
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
			// 如果将 Tmp 置于 i 节点处, 会破坏堆序性质, 需要将 i 节点的小儿子上移到 i 处.
			Elements[i] = Elements[Child];
		}
		else
		{
			// 可以将 Tmp 置于 i 节点处
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
	for (i = Index; i > 0; i /= 2) // 指针 i 起始于 Index, 向着父节点移动
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
		H->Elements[i] = H->Elements[i / 2]; // 将父节点下移
		i = i / 2; // 指针 i 向父节点移动
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
	LastElement = H->Elements[H->Size--]; // "Size--" 剪断了 LastElement 与父节点的连线

	// i 的左儿子在 2i 处, 右儿子在 2i+1 处
	for (i = 1; i * 2 <= H->Size; i = Child)
	{
		// 令 Child 指向左右儿子中的较小者
		Child = i * 2;
		if (Child < H->Size && // 防止 Child+1 越界. 该情形发生在当前的 H->Size 为偶数时
			H->Elements[Child] > H->Elements[Child + 1])
		{
			Child++;
		}

		// 将 Child 上移.
		// 假设 LastElement 与父节点的连线还存在, 此时如果 Child 和 LastElement
		// 有共同的父节点, 且 Child > LastElement, 那么将 Child 上移后, 循环结束
		// 后 i 指向 Child 原本的位置, LastElement 被移进该位置就会破坏堆序性质.
		// 在 binheap2.vsdx 中模拟 DeleteMin 的调用即可发现该问题.
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
// 堆排序:
// 1. 调用 BuildHeap() 将关键字序列堆序化, 复杂度为 O(N)
// 2. 调用 DeleteMin() 将关键字按升序输出,
//    需要调用 O(N) 次 DeleteMin(), DeleteMin() 的复杂度是 O(log N), 因此复杂度是 O(Nlog N)
//
// 所以, T(N) = O(N) + O(Nlog N) = O(Nlog N)
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