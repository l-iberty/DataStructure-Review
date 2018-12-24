#include "graph.h"

void dfs(Graph G, int v)
{
	Position p;

	visit(G->adj_list[v]->data);
	for (p = G->adj_list[v]->next; p; p = p->next)
	{
		// �������� v �ڽӵĶ������ dfs
		GraphVertex w = p->data;
		if (G->visited[w->value] == FALSE)
		{
			G->visited[w->value] = TRUE;
			dfs(G, w->value);
		}
	}
}