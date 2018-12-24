#include "graph.h"

void dfs(Graph G, int v)
{
	Position p;

	visit(G->adj_list[v]->data);
	for (p = G->adj_list[v]->next; p; p = p->next)
	{
		// 对所有与 v 邻接的顶点调用 dfs
		GraphVertex w = p->data;
		if (G->visited[w->value] == FALSE)
		{
			G->visited[w->value] = TRUE;
			dfs(G, w->value);
		}
	}
}