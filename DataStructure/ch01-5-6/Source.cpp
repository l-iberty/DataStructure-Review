#include <stdio.h>
#include <stdlib.h>

typedef struct _Set {
	int *data;
	int capacity;
	int length;
} *Set;

Set CreateSet(int capacity)
{
	Set set = (Set)malloc(sizeof(struct _Set));
	set->data = (int*)malloc(sizeof(int) * capacity);
	set->capacity = capacity;
	set->length = 0;
	return set;
}

void Insert(Set set, int v)
{
	int i;
	if (set->length < set->capacity)
	{
		for (i = 0; i < set->length; i++)
		{
			if (set->data[i] == v)
				break; /* 查找到重复元素 */
		}
		if (i == set->length) /* 未找到重复元素, 允许插入 */
			set->data[set->length++] = v;
	}
	else
	{
		printf("Inset Error\n");
	}
}

void DispSet(Set set)
{
	for (int i = 0; i < set->length; i++)
	{
		printf("%d ", set->data[i]);
	}
	printf("\n");
}

void FreeSet(Set set)
{
	free(set->data);
	free(set);
}

void Intersect(Set A, Set B, Set C)
{
	int i, j, k;

	/* 扫描A, 对于A中的每个元素, 若在B中找到与之相同的, 则将其插入C */

	k = 0;
	for (i = 0; i < A->length; i++)
	{
		for (j = 0; j < B->length; j++)
		{
			if (B->data[j] == A->data[i])
			{
				/* 集合中不包含重复元素, 所以以下语句不会造成元素被重复插入到集合C中 */
				C->data[k++] = A->data[i];
			}
		}
	}
	C->length = k;
}

void Union(Set A, Set B, Set C)
{
	int i, j, k;

	/* Copy A to C */
	for (i = 0; i < A->length; i++)
	{
		C->data[i] = A->data[i];
	}

	/* 扫描B, 对于B中的每个元素, 若没有在A中找到与之相同的, 则将其插入C */
	for (j = 0; j < B->length; j++)
	{
		for (k = 0; k < A->length; k++)
		{
			if (B->data[j] == A->data[k])
				break;
		}
		if (k >= A->length) /* not found */
			C->data[i++] = B->data[j];
	}
	C->length = i;
}

int main()
{
	Set A = CreateSet(5);
	Set B = CreateSet(8);
	Set C = CreateSet(13);
	Set D = CreateSet(13);

	Insert(A, 2);
	Insert(A, 4);
	Insert(A, 3);
	Insert(A, 6);
	Insert(A, 9);
	Insert(B, 10);
	Insert(B, 8);
	Insert(B, 14);
	Insert(B, 6);
	Insert(B, 9);
	Insert(B, 6);
	Insert(B, 9);
	Insert(B, 2);

	printf("A: ");
	DispSet(A);

	printf("B: ");
	DispSet(B);

	Intersect(A, B, C);
	printf("C: ");
	DispSet(C);

	Union(A, B, D);
	printf("D: ");
	DispSet(D);

	FreeSet(A);
	FreeSet(B);
	FreeSet(C);
	FreeSet(D);
}