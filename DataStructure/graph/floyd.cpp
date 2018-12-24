#include <stdio.h>
#include "graph.h"

void print_matrix(int a[N][N])
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		printf("\n------------------------\n");
		for (j = 0; j < N; j++)
		{
			printf(" %3d |", a[i][j]);
		}
	}
	printf("\n------------------------\n");
}

void floyd(int adj_matrix[N][N], int dist[N][N], int path[N][N])
{
	int i, j, k;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			dist[i][j] = adj_matrix[i][j];
			if (i == j || adj_matrix[i][j] == INFINITY)
				path[i][j] = -1;
			else
				path[i][j] = i;
		}
	}

	printf("++++++++++++++++++++++++++++++\n");
	//printf("dist(%d):", -1);
	//print_matrix(dist);
	printf("path(%d):", -1);
	print_matrix(path);
	
	for (k = 0; k < N; k++)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
		printf("++++++++++++++++++++++++++++++\n");
		//printf("dist(%d):", k);
		//print_matrix(dist);
		printf("path(%d):", k);
		print_matrix(path);
	}
}
