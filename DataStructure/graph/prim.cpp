#include "graph.h"

Table prim(Graph G, int start_vertex)
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
		print_edge(T->entries[v]->path, v);

		for (p = G->adj_list[v]->next; p; p = p->next)
		{
			GraphVertex w = p->data;
			if (T->entries[w->value]->known == FALSE)
			{
				if (w->weight < T->entries[w->value]->dist)
				{
					T->entries[w->value]->dist = w->weight;
					T->entries[w->value]->path = v;
				}
			}
		}
	}
	return T;
}
