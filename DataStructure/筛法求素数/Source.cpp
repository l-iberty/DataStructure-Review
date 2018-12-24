#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define SQRT(x) sqrt((float)(x))

void get_prime()
{
	int n[N + 1];
	int i, j;

	for (i = 0; i < _countof(n); i++)
		n[i] = 0;

	for (i = 2; i <= SQRT(N); i++)
	{
		for (j = i; i * j <= N; j++)
			n[i*j] = 1;
	}

	for (i = 2; i <= N; i++)
	{
		if (n[i] == 0)
			printf("%d ", i);
	}
}

int main()
{
	get_prime();
}