#include "graph.h"
#include <stdio.h>

// Test 1
// Bfs, Dfs, TopSort
// p218 Í¼9-4
void test1()
{
	Graph G = init_graph(7);
	
	add_vertex(G, 1, 2, 1);
	add_vertex(G, 1, 3, 1);
	add_vertex(G, 1, 4, 1);
	add_vertex(G, 2, 4, 1);
	add_vertex(G, 2, 5, 1);
	add_vertex(G, 3, 6, 1);
	add_vertex(G, 4, 3, 1);
	add_vertex(G, 4, 6, 1);
	add_vertex(G, 4, 7, 1);
	add_vertex(G, 5, 4, 1);
	add_vertex(G, 5, 7, 1);
	add_vertex(G, 7, 6, 1);

	indegree_counter(G);
	print_graph(G);

	printf("\ndfs: ");
	dfs(G, 1);

	reset_visited(G);
	printf("\nbfs: ");
	bfs(G, 1);
	
	printf("\ntop sort1: ");
	top_sort(G);
	printf("\ntop sort2: ");
	indegree_counter(G);
	top_sort2(G);

	destory_graph(G);
}

// Test2
// ÎÞÈ¨×î¶ÌÂ·¾¶
// p222 Í¼9-14
void test2()
{
	Graph G = init_graph(7);
	
	add_vertex(G, 1, 2, 1);
	add_vertex(G, 1, 4, 1);
	add_vertex(G, 2, 4, 1);
	add_vertex(G, 2, 5, 1);
	add_vertex(G, 3, 1, 1);
	add_vertex(G, 3, 6, 1);
	add_vertex(G, 4, 3, 1);
	add_vertex(G, 4, 5, 1);
	add_vertex(G, 4, 6, 1);
	add_vertex(G, 4, 7, 1);
	add_vertex(G, 5, 7, 1);
	add_vertex(G, 7, 6, 1);

	print_graph(G);

	Table T = unweighted_shortest_path(G, 3);
	print_table(T);
	for (int i = 1; i <= G->nr_vertex; i++)
	{
		printf("path(3 -> %d): ", i);
		print_path(T, i);
		printf("\n");
	}
	destroy_table(T);
}

// Test3
// Dijikstra
// p225 Í¼9-20
void test3()
{
	Graph G = init_graph(7);
	
	add_vertex(G, 1, 2, 2);
	add_vertex(G, 1, 4, 1);
	add_vertex(G, 2, 4, 3);
	add_vertex(G, 2, 5, 10);
	add_vertex(G, 3, 1, 4);
	add_vertex(G, 3, 6, 5);
	add_vertex(G, 4, 3, 2);
	add_vertex(G, 4, 5, 2);
	add_vertex(G, 4, 6, 8);
	add_vertex(G, 4, 7, 4);
	add_vertex(G, 5, 7, 6);
	add_vertex(G, 7, 6, 1);

	print_graph(G);

	Table T = dijikstra(G, 1);
	print_table(T);
	for (int i = 1; i <= G->nr_vertex; i++)
	{
		printf("path(1 -> %d): ", i);
		print_path(T, i);
		printf("\n");
	}
	destroy_table(T);
}

// Test4
// Prim
// p237 Í¼9-48
void test4()
{
	Graph G = init_graph(7);
	
	add_vertex(G, 1, 2, 2);
	add_vertex(G, 1, 3, 4);
	add_vertex(G, 1, 4, 1);
	add_vertex(G, 2, 1, 2);
	add_vertex(G, 2, 4, 3);
	add_vertex(G, 2, 5, 10);
	add_vertex(G, 3, 1, 4);
	add_vertex(G, 3, 4, 2);
	add_vertex(G, 3, 6, 5);
	add_vertex(G, 4, 1, 1);
	add_vertex(G, 4, 2, 3);
	add_vertex(G, 4, 3, 2);
	add_vertex(G, 4, 5, 7);
	add_vertex(G, 4, 6, 8);
	add_vertex(G, 4, 7, 4);
	add_vertex(G, 5, 2, 10);
	add_vertex(G, 5, 4, 7);
	add_vertex(G, 5, 7, 6);
	add_vertex(G, 6, 3, 5);
	add_vertex(G, 6, 4, 8);
	add_vertex(G, 6, 7, 1);
	add_vertex(G, 7, 4, 4);
	add_vertex(G, 7, 5, 6);
	add_vertex(G, 7, 6, 1);

	print_graph(G);

	Table T = prim(G, 1);
	print_table(T);
	destroy_table(T);
}

// Test5
// Prim
// p256 Í¼9-82. ¶¥µã±àºÅ: A,B,C,... -> 1,2,3,...
void test5()
{
	Graph G = init_graph(10);

	add_vertex(G, 1, 2, 3);
	add_vertex(G, 1, 4, 4);
	add_vertex(G, 1, 5, 4);

	add_vertex(G, 2, 1, 3);;
	add_vertex(G, 2, 3, 10);
	add_vertex(G, 2, 5, 2);
	add_vertex(G, 2, 6, 3);

	add_vertex(G, 3, 2, 10);
	add_vertex(G, 3, 6, 6);
	add_vertex(G, 3, 7, 1);

	add_vertex(G, 4, 1, 4);
	add_vertex(G, 4, 5, 5);
	add_vertex(G, 4, 8, 6);

	add_vertex(G, 5, 1, 4);
	add_vertex(G, 5, 2, 2);
	add_vertex(G, 5, 4, 5);
	add_vertex(G, 5, 6, 11);
	add_vertex(G, 5, 8, 2);
	add_vertex(G, 5, 9, 1);

	add_vertex(G, 6, 2, 3);
	add_vertex(G, 6, 3, 6);
	add_vertex(G, 6, 5, 11);
	add_vertex(G, 6, 7, 2);
	add_vertex(G, 6, 9, 3);
	add_vertex(G, 6, 10, 11);

	add_vertex(G, 7, 3, 1);
	add_vertex(G, 7, 6, 2);
	add_vertex(G, 7, 10, 8);

	add_vertex(G, 8, 4, 6);
	add_vertex(G, 8, 5, 2);
	add_vertex(G, 8, 9, 4);

	add_vertex(G, 9, 5, 1);
	add_vertex(G, 9, 6, 3);
	add_vertex(G, 9, 8, 4);
	add_vertex(G, 9, 10, 7);

	add_vertex(G, 10, 6, 11);
	add_vertex(G, 10, 7, 8);
	add_vertex(G, 10, 9, 7);

	print_graph(G);

	Table T = prim(G, 1);
	print_table(T);
	destroy_table(T);
}

// Test6
// Floyd
void test6()
{
	int adj_matrix1[N][N]=
	{
		{0, 1, 4, INFINITY},
		{INFINITY, 0, 2, 5},
		{INFINITY, INFINITY, 0, 1},
		{2, INFINITY, INFINITY, 0}
	};
	int adj_matrix2[N][N]=
	{
		{0, 1, INFINITY, 4},
		{INFINITY, 0, 9, 2},
		{3, 5, 0, 8},
		{INFINITY, INFINITY, 6, 0}
	};
	int dist[N][N];
	int path[N][N];
	floyd(adj_matrix1, dist, path);
}

int main()
{
	test6();
}