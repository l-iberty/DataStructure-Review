#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////  List  /////////////////////// 

List create_list()
{
	List L;
	L = (List)malloc(sizeof(struct ListEntry));
	L->data = NULL;
	L->next = NULL;
	return L;
}

void push_front(List L, GraphVertex data)
{
	List node;
	node = (List)malloc(sizeof(struct ListEntry));
	node->data = data;
	node->next = L->next;
	L->next = node;
}

void push_back(List L, GraphVertex data)
{
	List node;
	Position p;

	for (p = L; p->next; p = p->next);
	node = (List)malloc(sizeof(struct ListEntry));
	node->data = data;
	node->next = NULL;
	p->next = node;
}

void print_list(List L)
{
	Position p;
	for (p = L->next; p; p = p->next)
	{
		printf("%d(%d) ", p->data->value, p->data->weight);
	}
	printf("\n");
}

void destroy_list(List L)
{
	Position p, next;
	for (p = L; p; p = next)
	{
		next = p->next;
		free(p->data);
		free(p);
	}
}

///////////////////////  Queue  /////////////////////// 

Queue create_queue()
{
	return create_list();
}

void enqueue(Queue Q, GraphVertex data)
{
	push_back(Q, data);
}

GraphVertex dequeue(Queue Q)
{
	GraphVertex v;

	if (empty_queue(Q))
	{
		fprintf(stderr, "Empty queue");
		exit(1);
	}
	v = Q->next->data;
	Q->next = Q->next->next;
	return v;
}

int empty_queue(Queue Q)
{
	return (Q->next == NULL);
}

void destroy_queue(Queue Q)
{
	destroy_list(Q);
}

///////////////////////  Graph  /////////////////////// 

Graph init_graph(int nr_vertex)
{
	Graph G;
	
	G = (Graph)malloc(sizeof(struct GraphEntry));
	G->nr_vertex = nr_vertex;
	G->adj_list = (List*)malloc((nr_vertex + 1) * sizeof(List));
	G->visited = (int*)malloc((nr_vertex + 1) * sizeof(int));
	G->indegree = (int*)malloc((nr_vertex + 1) * sizeof(int));
	
	for (int i = 1; i <= nr_vertex; i++)
	{
		GraphVertex v = make_graph_vertex(i, 0);
		G->adj_list[i] = create_list();
		G->adj_list[i]->data = v;
		G->visited[i] = FALSE;
		G->indegree[i] = 0;
	}
	return G;
}

// 添加序偶 (v,u), 边的权值 = weight
void add_vertex(Graph G, int v, int u, int weight)
{
	GraphVertex vertex;
	vertex = make_graph_vertex(u, weight);
	push_back(G->adj_list[v], vertex);
}

void print_graph(Graph G)
{
	for (int i = 1; i <= G->nr_vertex; i++)
	{
		printf("%d (indegree = %d) --> ",
			G->adj_list[i]->data->value, G->indegree[i]);
		print_list(G->adj_list[i]);
	}
}

void destory_graph(Graph G)
{
	for (int i = 1; i <= G->nr_vertex; i++)
	{
		destroy_list(G->adj_list[i]);
	}
	free(G->adj_list);
	free(G);
}

void visit(GraphVertex vertex)
{
	printf("%d ", vertex->value);
}

void reset_visited(Graph G)
{
	memset(G->visited, 0, (G->nr_vertex + 1) * sizeof(int));
}

GraphVertex make_graph_vertex(int value, int weight)
{
	GraphVertex vertex;
	vertex = (GraphVertex)malloc(sizeof(struct GraphVertexEntry));
	vertex->value = value;
	vertex->weight = weight;
	return vertex;
}

void print_edge(int v, int u)
{
	if (v != 0 && u != 0)
		printf("(%d,%d)\n", v, u);
}
