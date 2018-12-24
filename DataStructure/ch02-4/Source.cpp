#include <stdio.h>

#define N 5


/**
 * ����: �����е���Сֵ, �����е����ֵ
 */
void Andian(int A[][N], int row)
{
	int i, j, k, r, max, min;

	for (i = 0; i < row; i++)
	{
		// ���ҵ� i ���е���С�� min
		k = 0;
		min = A[i][0];
		for (j = 0; j < N - 1; j++)
		{
			if (A[i][j + 1] < min)
			{
				min = A[i][j + 1];
				k = j + 1;
			}
		}
		// min �Ƿ�����������(�� k ��)�е������?
		r = 0;
		max = A[0][k];
		for (j = 0; j < row - 1; j++)
		{
			if (A[j + 1][k] > max)
			{
				max = A[j + 1][k];
				r = j + 1;
			}
		}
		if (max == min)
		{
			printf("A[%d][%d] = %d\n", r, k, A[r][k]);
		}
	}
}

int findMax(int A[], int n)
{
	int max;

	max = A[0];
	for (int i = 0; i < n - 1; i++)
	{
		if (max < A[i + 1])
		{
			max = A[i + 1];
		}
	}
	return max;
}

int main()
{
	int A[5][N] = {
		{ 0, 4, 9, 8, 2 },
		{ 5, 6, 10, 5, 7 },
		{ 16, 20, 15, 18, 18 }, // 15
		{ 6, 12, 8, 1, 9 },
		{ 1, 3, 9, 9, 10 }
	};
	Andian(A, 5);
}