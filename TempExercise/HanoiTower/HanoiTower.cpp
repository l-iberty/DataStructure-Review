#include <stdio.h>

// a ������ n ������, �����ǽ��� b �̰ᵽ c ��
void hanoi(int n, int a, int b, int c)
{
	if (n == 1)
	{
		printf("%d -> %d\n", a, c);
	}
	else
	{
		// �� a ���ϵ� n-1 �����ӽ��� c �̰ᵽ b ��
		hanoi(n - 1, a, c, b);
		// �� a ���ϵ�����Ǹ����Ӱᵽ c ��
		printf("%d -> %d\n", a, c);
		// �� b ���ϵ� n-1 �����ӽ��� a �̰ᵽ c ��
		hanoi(n - 1, b, a, c);
	}
}

int main()
{
	hanoi(3, 1, 2, 3);
}