#include <stdio.h>

#define N 11

void reverse(int A[], int length)
{
	int t;

	for (int i = 0; i < length / 2; i++)
	{
		t = A[i];
		A[i] = A[length - i - 1];
		A[length - i - 1] = t;
	}
}

void insert(int A[], int length, int x)
{
	int i, j;

	/* 找到插入位置 */
	i = 0;
	while (i < length && A[i] < x) { i++; }

	/* 将 i 以后的元素后移 */
	/* 后移时如果从 i 开始向后进行, 则需要使用临时变量 */
	for (j = length; j >= i; j--)
		A[j + 1] = A[j];

	A[i] = x;
}

void print(int A[], int length)
{
	for (int i = 0; i < length; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
{
	int A[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int B[N] = { 5, 7, 9, 10, 15, 15, 16, 18, 30 };

	reverse(A, N);
	print(A, N);

	insert(B, 9, 1);
	print(B, N);
}