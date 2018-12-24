#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void indegree_counter(Graph G)
{
	for (int i = 1; i <= G->nr_vertex; i++)
		count_indegree(G, i);
}

void count_indegree(Graph G, int v)
{
	Position p;

	for (int i = 1; i <= G->nr_vertex; i++)
	{
		for (p = G->adj_list[i]->next; p; p = p->next)
		{
			if (p->data->value == v)
				G->indegree[v]++;
		}
	}
}

int find_vertex_of_zero_indgree(Graph G)
{
	int i;
	for (i = 1; i <= G->nr_vertex; i++)
	{
		if (G->visited[i] == FALSE && G->indegree[i] == 0)
			break;
	}
	if (i <= G->nr_vertex)
		return i;
	else
		return -1;
}

// O(V^2)
void top_sort(Graph G)
{
	int i, v;
	Position p;

	reset_visited(G);

	for (i = 1; i <= G->nr_vertex; i++)
	{
		v = find_vertex_of_zero_indgree(G);
		if (v != -1)
		{
			G->visited[v] = TRUE; // 表示该顶点已被输出到拓扑排序序列中
			printf("%d ", v);

			// 所有与 v 邻接的顶点的入度减1
			for (p = G->adj_list[v]->next; p; p = p->next)
			{
				G->indegree[p->data->value]--;
			}
		}
		else if (i < G->nr_vertex)
		{
			printf("Graph has a circle");
			return;
		}
	}
}

// O(V+E)
void top_sort2(Graph G)
{
	Queue Q;
	int counter;
	GraphVertex v, w;
	Position p;

	Q = create_queue();

	for (int i = 1; i <= G->nr_vertex; i++)
	{
		if (G->indegree[i] == 0)
			enqueue(Q, make_graph_vertex(i, 0));
	}

	counter = 0;
	while (!empty_queue(Q))
	{
		v = dequeue(Q);
		counter++;
		printf("%d ", v->value);

		for (p = G->adj_list[v->value]->next; p; p = p->next)
		{
			w = p->data;
			if (--G->indegree[w->value] == 0)
				enqueue(Q, w);
		}
	}

	if (counter != G->nr_vertex)
		fprintf(stderr, "Graph has a circle");

	destroy_queue(Q);
}
