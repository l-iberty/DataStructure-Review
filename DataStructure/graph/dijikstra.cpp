#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// 使用二叉堆实现的 PriorityQueue 时, 遇到了 p226~p227 所述的
// 关于 DecreaseKey 的难题.
Table dijikstra(Graph G, int start_vertex)
{
	Table T;
	Position p;

	T = init_table(G->nr_vertex, 1);

	for (;;)
	{
		int v = find_smallest_unknown_dist(T);
		if (v == -1)
			break;

		T->entries[v]->known = TRUE;

		for (p = G->adj_list[v]->next; p; p = p->next)
		{
			GraphVertex w = p->data;
			if (T->entries[w->value]->known == FALSE)
			{
				if (T->entries[v]->dist + w->weight < T->entries[w->value]->dist)
				{
					T->entries[w->value]->dist = T->entries[v]->dist + w->weight;
					T->entries[w->value]->path = v;
				}
			}
		}
	}
	return T;
}