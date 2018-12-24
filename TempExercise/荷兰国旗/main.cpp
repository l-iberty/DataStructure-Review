#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define WHITE 1
#define BLUE 2

inline void print_array(int x[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", x[i]);
	printf("\n");
}

void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}

// ��׼������������
void solve1(int x[], int n)
{
	int begin, end, current;
	begin = 0;
	end = n - 1;
	current = 0;
	while (current <= end)
	{
		switch (x[current])
		{
		case RED:
			swap(x[begin++], x[current++]);
			break;
		case WHITE:
			current++;
			break;
		case BLUE:
			swap(x[end--], x[current]);
			break;
		}
	}
}

// ���������ʽ1�����������а�������0����������
void solve2(int x[], int n)
{
	int begin, end, current;
	begin = 0;
	end = n - 1;
	current = 0;
	while (current <= end)
	{
		if (x[current] < 0)
			swap(x[begin++], x[current++]);
		else if (x[current] > 0)
			swap(x[end--], x[current]);
		else // x[current] == 0
			current++;
	}
}

// ���������ʽ2���������Ƶ�ǰ��ȥ
void solve3(int x[], int n)
{
	int begin, end, current;
	begin = 0;
	end = n - 1;
	current = 0;
	while (current <= end)
	{
		if (x[current] % 2 != 0)
			swap(x[begin++], x[current]);
		current++;
	}
}

void test1()
{
	int x[] = { 1, 2, 0, 0, 2, 2, 1, 1, 1, 0, 0, 2, 1, 2, 0, 0, 1, 1, 2, 2, 0 };
	solve1(x, _countof(x));
	print_array(x, _countof(x));
}

void test2()
{
	int x[] = { 1, 4, 5, 0, -1, 9, -4, 0, 0, -1, -4, -12, 12, 0, 6 };
	solve2(x, _countof(x));
	print_array(x, _countof(x));
}

void test3()
{
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 9, 8, 12, 7, 34, 17, 29 };
	solve3(x, _countof(x));
	print_array(x, _countof(x));
}

int main()
{
	test3();
}