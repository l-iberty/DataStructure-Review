#include <stdio.h>

// a 盘上有 n 个盘子, 把它们借助 b 盘搬到 c 盘
void hanoi(int n, int a, int b, int c)
{
	if (n == 1)
	{
		printf("%d -> %d\n", a, c);
	}
	else
	{
		// 把 a 盘上的 n-1 个盘子借助 c 盘搬到 b 盘
		hanoi(n - 1, a, c, b);
		// 把 a 盘上的最后那个盘子搬到 c 盘
		printf("%d -> %d\n", a, c);
		// 把 b 盘上的 n-1 个盘子借助 a 盘搬到 c 盘
		hanoi(n - 1, b, a, c);
	}
}

int main()
{
	hanoi(3, 1, 2, 3);
}