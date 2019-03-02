#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define OUTPUT

#define N 10
#define MINDATA -1 // for heap-sort

void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}

void print(int x[], int len)
{
	int i;
	for (i = 0; i < len; i++)
		printf("%d ", x[i]);
	printf("\n");
}

///////////////////////////////////////////////////////////

void BubbleSort(int x[], int len)
{
	int i, j, pass;
	clock_t start, end;
	
	printf("\nBubbleSort begins...\n");
	start = clock();
	
	pass = 1;
	for (i = 1; i < len; i++)
	{
		for (j = 0; j < len - i; j++)
		{
			if (x[j] > x[j + 1])
				swap(x[j], x[j + 1]);
		}
#ifdef OUTPUT
		printf("%d:\t", pass++);
		print(x, len);
#endif
	}
	
	end = clock();
	printf("BubbleSort ends. Time elapsed: %.3f s\n", 
		(double)(end - start) / CLOCKS_PER_SEC);
}

///////////////////////////////////////////////////////////

void InsertSort(int x[], int len)
{
	int i, j, temp, pass;
	clock_t start, end;

	printf("\nInsertSort begins...\n");
	start = clock();

	pass = 1;
	for (i = 1; i < len; i++)
	{
		temp = x[i];
		for (j = i; j > 0; j--)
		{
			if (temp < x[j - 1])
				x[j] = x[j - 1];
			else
				break;
		}
		x[j] = temp;
#ifdef OUTPUT
		printf("%d:\t", pass++);
		print(x, len);
#endif
	}

	end = clock();
	printf("InsertSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);
}

///////////////////////////////////////////////////////////

void SelectSort(int x[], int len)
{
	int i, j, min, pass;
	clock_t start, end;

	printf("\nSelectSort begins...\n");
	start = clock();

	pass = 1;
	for (i = 0; i < len; i++)
	{
		min = i;
		for (j = i; j < len; j++)
		{
			if (x[j] < x[min])
				min = j;
		}
		swap(x[i], x[min]);
#ifdef OUTPUT
		printf("%d:\t", pass++);
		print(x, len);
#endif
	}

	end = clock();
	printf("SelectSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);
}

///////////////////////////////////////////////////////////

void ShellSort(int x[], int len)
{
	int i, j, increment, temp, pass;
	clock_t start, end;

	printf("\nShellSort begins...\n");
	start = clock();

	pass = 1;
	for (increment = len / 2; increment > 0; increment /= 2)
	{
		for (i = increment; i < len; i++)
		{
			temp = x[i];
			for (j = i; j >= increment; j -= increment)
			{
				if (temp < x[j - increment])
					x[j] = x[j - increment];
				else
					break;
			}
			x[j] = temp;
#ifdef OUTPUT
			printf("%d:\t", pass++);
			print(x, len);
#endif
		}
	}

	end = clock();
	printf("ShellSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);
}

///////////////////////////////////////////////////////////

void PercolateDown(int x[], int len, int index)
{
	int i, child;
	int temp;

	temp = x[index];
	for (i = index; i * 2 <= len; i = child)
	{
		// Find smaller child.
		child = i * 2;
		if (child < len &&
			x[child + 1] < x[child])
		{
			child++;
		}

		if (temp > x[child])
			x[i] = x[child];
		else
			break;
	}
	x[i] = temp;
}

void HeapSort(int x[], int len)
{
	int i, child;
	int last;
	clock_t start, end;

	printf("\nHeapSort begins...\n");
	start = clock();

	// BuildHeap -- O(N)
	for (i = len / 2; i > 0; i--)
		PercolateDown(x, len, i);

	while (len > 0)
	{
		// DeleteMin -- O(N logN)
		last = x[len--];
#ifdef OUTPUT
		printf("%d ", x[1]); // output min
#endif // OUTPUT
		for (i = 1; i * 2 <= len; i = child)
		{
			child = i * 2;
			if (child < len &&
				x[child + 1] < x[child])
			{
				child++;
			}

			if (x[child] < last)
				x[i] = x[child];
			else
				break;
		}
		x[i] = last;
	}

	end = clock();
	printf("\nHeapSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);
}

///////////////////////////////////////////////////////////

void Merge(int x[],
	int c[], 
	int left_start, int left_end, 
	int right_start, int right_end)
{
	int a_ptr, b_ptr, c_ptr, i;

	a_ptr = left_start;
	b_ptr = right_start;
	c_ptr = 0;

	while (a_ptr <= left_end && b_ptr <= right_end)
	{
		if (x[a_ptr] < x[b_ptr])
			c[c_ptr++] = x[a_ptr++];
		else
			c[c_ptr++] = x[b_ptr++];
	}

	while (a_ptr <= left_end)
		c[c_ptr++] = x[a_ptr++];
	while (b_ptr <= right_end)
		c[c_ptr++] = x[b_ptr++];

	c_ptr = 0;
	for (i = left_start; i <= right_end; i++)
		x[i] = c[c_ptr++];
}

void MSort(int x[], int c[], int left, int right)
{
	int center;

	if (left < right)
	{
		center = (left + right) / 2;
		MSort(x, c, left, center);
		MSort(x, c, center + 1, right);
		Merge(x, c, left, center, center + 1, right);
	}
}

void MergeSort(int x[], int len)
{
	int *c;
	clock_t start, end;

	c = (int*)malloc(len * sizeof(int));

	printf("\nMergeSort begins...\n");
	start = clock();

	MSort(x, c, 0, len - 1);
	
	end = clock();
	printf("MergeSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);

	free(c);

#ifdef OUTPUT
	print(x, len);
#endif
}

///////////////////////////////////////////////////////////

void QSort(int x[], int left, int right)
{
	int i, j, pivot;

	if (left < right)
	{
		i = left, j = right - 1;
		pivot = x[left];
		swap(x[left], x[right]);

		for (;;)
		{
			while (i <= right && x[i] < pivot) i++;
			while (j >= left && x[j] > pivot) j--;

			if (i < j) swap(x[i++], x[j--]);
			else break;
		}
		swap(x[i], x[right]);
		QSort(x, left, i - 1);
		QSort(x, i + 1, right);
	}
}

void QuickSort(int x[], int len)
{
	clock_t start, end;

	printf("\nQuickSort begins...\n");
	start = clock();

	QSort(x, 0, len - 1);

	end = clock();
	printf("\nQuickSort ends. Time elapsed: %.3f s\n",
		(double)(end - start) / CLOCKS_PER_SEC);
#ifdef OUTPUT
	print(x, len);
#endif
}

///////////////////////////////////////////////////////////

int main()
{
	int i;
	int *x1, *x2, *x3, *x4, *x5, *x6, *x7;

	x1 = (int*)malloc((N + 1) * sizeof(int));
	x2 = (int*)malloc((N + 1) * sizeof(int));
	x3 = (int*)malloc((N + 1) * sizeof(int));
	x4 = (int*)malloc((N + 1) * sizeof(int));
	x5 = (int*)malloc((N + 1) * sizeof(int));
	x6 = (int*)malloc((N + 1) * sizeof(int));
	x7 = (int*)malloc((N + 1) * sizeof(int));
	if (!x1 || !x2 || !x3 || !x4 || !x5 || !x6 || !x7)
	{
		printf("Memory space not enougth.\n");
		return 0;
	}

	x1[0] = MINDATA;
	srand((unsigned int)time(NULL));
	for (i = 1; i <= N; i++)
	{
		x1[i] = rand() % (N * 5);
		printf("%d ", x1[i]);
	}
	printf("\n");

	memcpy(x2, x1, (N + 1)*sizeof(int));
	memcpy(x3, x1, (N + 1)*sizeof(int));
	memcpy(x4, x1, (N + 1)*sizeof(int));
	memcpy(x5, x1, (N + 1)*sizeof(int));
	memcpy(x6, x1, (N + 1)*sizeof(int));
	memcpy(x7, x1, (N + 1)*sizeof(int));

	//BubbleSort(x1 + 1, N);
	//SelectSort(x2 + 1, N);
	//InsertSort(x3 + 1, N);
	//HeapSort(x4, N);
	//ShellSort(x5 + 1, N);
	//MergeSort(x6 + 1, N);
	QuickSort(x7 + 1, N);

	free(x1);
	free(x2);
	free(x3);
	free(x4);
	free(x5);
	free(x6);
	free(x7);
}